#include "functionsforserver.h"

QByteArray parsing(QString data_from_client)
{
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&')); // Разбиваем полученные данные от клиента на список строк
    QString nameOfFunc = data_from_client_list.front(); // Получаем имя функции из первой строки списка
    data_from_client_list.pop_front(); // Удаляем первую строку списка

    if (nameOfFunc == "auth")
        return auth(data_from_client_list.at(0), data_from_client_list.at(1)); // Вызываем функцию аутентификации и возвращаем результат
    else if (nameOfFunc == "reg")
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2)); // Вызываем функцию регистрации и возвращаем результат
    else
        return "error"; // Если получено неизвестное имя функции, возвращаем ошибку
}

QByteArray auth(QString log, QString pass)
{
    QString result = DataBase::getInstance()->sendQuery("SELECT * FROM users WHERE login = '" + log + "' AND password = '" + pass + "'"); // Отправляем запрос на аутентификацию в базу данных
    if (result == "auth_ok")
    {
        return "auth_ok"; // Если аутентификация прошла успешно, возвращаем "auth_ok"
    }
    else if (result == "auth_err")
    {
        return "auth_err"; // Если ошибка аутентификации, возвращаем "auth_err"
    }
    else if (result == "auth_false")
    {
        return "auth_false"; // Если аутентификация неудачна, возвращаем "auth_false"
    }
    else
    {
        return "error"; // Если произошла ошибка, возвращаем ошибку
    }
}

QByteArray reg(QString log, QString pass, QString mail)
{
    // Регистрация нового пользователя в БД
    return "reg"; // Возвращает "reg" (заглушка)
}
