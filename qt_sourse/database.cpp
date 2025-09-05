#include "database.h"

QSqlDatabase database :: db = QSqlDatabase :: addDatabase("QODBC");
QSqlQuery * database :: sql = NULL;
database::database()
{
    qDebug()<<"数据库已经创建";
}
bool database::getConnnection()
{
    db.setHostName("127.0.0.1");                                                 //绑定数据库IP路径
    db.setPort(3306);                                                            //绑定数据库端口号
    db.setDatabaseName("ShipDesignandManagement");                               //绑定ODBC数据源名称
    db.setUserName("root");                                                      //绑定数据库系统用户名
    db.setPassword("SHWYH");                                                     //输入数据库系统登录密码
    if(!db.open())
    {
        qDebug()<<"DataBase ERROR";
        qDebug()<<db.lastError().text();
        return false;
    }
    else
    {
        qDebug()<<"Connection succeed!";
        return true;
    }
}
void database::quitConnection()
{
    db.close();     //断开数据库连接
    qDebug()<<"Close successfully!";
}
