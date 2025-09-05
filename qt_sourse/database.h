#ifndef DATABASE_H
#define DATABASE_H
// #include <QSql.h>             //打成Qsql！了
#include <QtSql/qtsqlglobal.h>   //报错显示的新接口
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


class database
{
public:
    database();

    //数据库连接的相关函数
    static bool getConnnection();  //获得数据库连接
    static void quitConnection();  //断开数据库连接
private:
    static QSqlDatabase db;  //定义静态变量db（databse）作为数据库的实例
    static QSqlQuery  *sql;  //定义静态变量sql作为数据库执行语言实例
};

#endif // DATABASE_H
