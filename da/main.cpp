#include <QCoreApplication>
#include "mytcpserver.h"
#include "dataBase.h"

DataBase *DataBase::p_instance = nullptr; // Инициализация статического указателя на экземпляр базы данных (Singleton)
DataBaseDestroyer DataBase::destroyer; // Инициализация экземпляра класса DataBaseDestroyer
QSqlDatabase DataBase::db; // Инициализация объекта базы данных

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Создаем экземпляр приложения Qt
    MyTcpServer myserv; // Создаем экземпляр класса MyTcpServer
    return a.exec(); // Запускаем цикл обработки событий приложения Qt
}
