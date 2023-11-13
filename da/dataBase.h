#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

// Класс, отвечающий за управление уничтожением экземпляра класса DataBase
class DataBaseDestroyer
{
private:
    DataBase *dataBasePointer;

public:
    ~DataBaseDestroyer()
    {
        delete dataBasePointer;
    }
    void initialize(DataBase *p) { dataBasePointer = p; }
};

// Класс, представляющий базу данных (Singleton)
class DataBase
{
private:
    static DataBase *p_instance; // Статический указатель на единственный экземпляр класса
    static DataBaseDestroyer destroyer; // Экземпляр класса DataBaseDestroyer для уничтожения базы данных
    static QSqlDatabase db; // Объект базы данных

protected:
    DataBase()
    {
        db = QSqlDatabase::addDatabase("QSQLITE"); // Устанавливаем тип базы данных (в данном случае, SQLite)
        db.setDatabaseName("Test.db"); // Устанавливаем имя базы данных

        if (!db.open()) // Проверяем, удалось ли открыть базу данных
            qDebug() << db.lastError().text(); // Если нет, выводим ошибку
    }

    DataBase(const DataBase &) = delete; // Запрещаем копирование объекта базы данных
    DataBase &operator=(DataBase &) = delete; // Запрещаем присваивание объекта базы данных

    ~DataBase()
    {
        db.close(); // Закрываем базу данных
    }

    friend class DataBaseDestroyer; // Разрешаем классу DataBaseDestroyer доступ к закрытым членам класса DataBase

public:
    static DataBase *getInstance() // Получение экземпляра базы данных (Singleton)
    {
        if (!p_instance) // Если экземпляр еще не создан
        {
            p_instance = new DataBase(); // Создаем экземпляр базы данных
            destroyer.initialize(p_instance); // Инициализируем экземпляр класса DataBaseDestroyer
        }
        return p_instance; // Возвращаем экземпляр базы данных
    }

    static QString sendQuery(QString str)
    {
        // Ваша логика запроса к БД
        return "dfgh";
    }
};

DataBase *DataBase::p_instance = nullptr; // Инициализация статического указателя на экземпляр базы данных (Singleton)
DataBaseDestroyer DataBase::destroyer; // Инициализация экземпляра класса DataBaseDestroyer
QSqlDatabase DataBase::db; // Инициализация объекта базы данных

#endif // DATABASE_H
