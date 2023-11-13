#include "mytcpserver.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close(); // Закрываем серверное соединение
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this); // Создаем серверное соединение
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection); // Подключаем сигнал о новом соединении к соответствующему слоту

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) // Запускаем серверное соединение на всех доступных сетевых интерфейсах на порту 33333
    {
        qDebug() << "server is not started"; // Если серверное соединение не удалось запустить, выводим сообщение
    }
    else
    {
        qDebug() << "server is started"; // Если серверное соединение запущено успешно, выводим сообщение
    }
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection(); // Принимаем новое клиентское соединение
    mTcpSocket->write("Hello, World!!! I am echo server!\r\n"); // Отправляем приветственное сообщение клиенту
    connect(mTcpSocket, &QTcpSocket::readyRead this, &MyTcpServer::slotServerRead); // Подключаем сигнал о доступности данных для чтения к соответствующему слоту
    connect(mTcpSocket, &QTcpSocket::disconnected,
            this, &MyTcpServer::slotClientDisconnected); // Подключаем сигнал об отключении клиента к соответствующему слоту
    qDebug() << "New connection"; // Выводим сообщение о новом клиентском соединении
}

void MyTcpServer::slotServerRead()
{
    QString res = "";
    while (mTcpSocket->bytesAvailable() > 0) // Пока есть доступные данные для чтения в сокете
    {
        QByteArray array = mTcpSocket->readAll(); // Читаем все доступные данные
        res.append(array); // Добавляем прочитанные данные в переменную res
    }
    qDebug() << res; // Выводим прочитанные данные
    mTcpSocket->write(parsing(res)); // Отправляем результат парсинга данных обратно клиенту
}

void MyTcpServer::slotClientDisconnected()
{
    mTcpSocket->close(); // Закрываем клиентское соединение
}
