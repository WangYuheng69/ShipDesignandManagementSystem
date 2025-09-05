#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "managerpage.h"
#include "designerpage.h"
#include "approverpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->myDatabase.getConnnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString userIuputtype;
    if(ui->radioButtonone->isChecked())
    {
        userIuputtype = "Designer";               //设计师
    }
    else
    {
        if(ui->radioButtontwo->isChecked())
        {
            userIuputtype = "Project Manager";   //项目经理
        }
        else
        {
            userIuputtype = "Approver";          //审批员
        }
    }
    QString userInputNumber = ui->InputNumber->text();
    QString userInputPassword = ui->InputPassword->text();
    qDebug()<<"用户输入的ID:"+userInputNumber;
    qDebug()<<"输入的密码:"+userInputPassword;
    qDebug()<<"用户身份:"+userIuputtype;


    if(ui->radioButtontwo->isChecked())
    {
        QSqlQuery sql;
        sql.prepare("select * from manager where managerid = :userInputNumber");
        sql.bindValue(":userInputNumber",userInputNumber);
        sql.exec();
        QString userNumber;
        QString userPassword;//还有其他的列！！
        while(sql.next())
        {
            userNumber = sql.value("managerid").toString();//mysql数据库的字段名不要有大写字母
            userPassword = sql.value("password").toString();
        }
        qDebug()<<"数据库找到的ID:"+userNumber;
        qDebug()<<"数据库找到的密码"+userPassword;
        sql.clear();
        if(userInputNumber == userNumber&&userInputPassword == userPassword)
        {
            qDebug()<<"登录成功！！";
            //跳转界面
            this->~MainWindow();
            managerpage * w = new managerpage();
            w->show();
            qDebug()<<"进入项目经理管理界面";
        }
        else
        {
            qDebug()<<"输入的ID或密码错误！！";
        }
    }
    else if(ui->radioButtonone->isChecked())
    {
        QSqlQuery sql;
        sql.prepare("select * from designer where designerid = :userInputNumber");
        sql.bindValue(":userInputNumber",userInputNumber);
        sql.exec();
        QString userNumber;
        QString userPassword;
        while(sql.next())
        {
            userNumber = sql.value("designerid").toString();
            userPassword = sql.value("password").toString();
        }
        qDebug()<<"数据库找到的ID:"+userNumber;
        qDebug()<<"数据库找到的密码"+userPassword;
        sql.clear();
        if(userInputPassword == userPassword && userInputNumber == userNumber)
        {
            qDebug()<<"登录成功！！";
            this->~MainWindow();
            designerpage * w = new designerpage();
            w->show();
            qDebug()<<"进入项目经理管理界面";
        }
        else
        {
            qDebug()<<"输入的ID或密码错误！！";
        }
    }
    else if(ui->radioButtonthreee->isChecked())
    {
        QSqlQuery sql;
        sql.prepare("select * from approver where approverid = :userInputNumber");
        sql.bindValue(":userInputNumber",userInputNumber);
        sql.exec();
        QString userNumber;
        QString userPassword;
        while(sql.next())
        {
            userNumber = sql.value("approverid").toString();
            userPassword = sql.value("password").toString();
        }
        qDebug()<<"数据库找到的ID:"+userNumber;
        qDebug()<<"数据库找到的密码"+userPassword;
        sql.clear();
        if(userInputPassword == userPassword && userInputNumber == userNumber)
        {
            qDebug()<<"登录成功！！";
            this->~MainWindow();
            approverpage * w = new approverpage();
            w->show();
            qDebug()<<"进入项目经理管理界面";
        }
        else
        {
            qDebug()<<"输入的ID或密码错误！！";
        }
    }


}


