#include "approverpage.h"
#include "ui_approverpage.h"
#include "mainwindow.h"

approverpage::approverpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::approverpage)
{
    ui->setupUi(this);

    //连接数据库
    this->myDatabase.getConnnection();

    qDebug()<<"进入approverpage!";

    //为表格模式指针指定内存
    this->dataTableModel = new QStandardItemModel();

    ui->controlPage_3->setCurrentIndex(0);
}

approverpage::~approverpage()
{
    delete ui;
}

void approverpage::setTableinfo()
{
    //设置表头
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Recordid"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Fileid"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Filename"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Changewhy"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Changedate"));
    this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("Approverid"));
    //设置表格信息
    this->getTableInfo();

    //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
    ui->cardTable->setColumnWidth(0,80);
    ui->cardTable->setColumnWidth(1,80);
    ui->cardTable->setColumnWidth(2,100);
    ui->cardTable->setColumnWidth(3,80);
    ui->cardTable->setColumnWidth(4,120);
    ui->cardTable->setColumnWidth(5,80);

    //设置表格只读属性
    ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //将设计好的表格模式，装载到表格上
    ui->cardTable->setModel(this->dataTableModel);
}



void approverpage::getTableInfo()
{
    //第一步，从数据库中获取信息
    QSqlQuery sql;
    sql.prepare("select * from approvefile");//select from 大小写都行
    sql.exec();

    int row = 0;
    while(sql.next())
    {   //将数据库中的表填入表格中
        this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("recordid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("fileid").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("filename").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("changewhy").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("changedate").toString()));
        this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("Approverid").toString()));
        row++;
    }
    sql.clear();
}



void approverpage::on_pushButton_approvealter_clicked()
{
    QString recordid = ui->choooserecordid->text();        //approver输入recordid
    QString fileid = ui->thefileid->text();                //approver确认fileid
    QString changereason = ui->changeforwhat->text();      //approver输入changereason
    QString changetime = ui->thechangedate->text();        //approver输入thechangedate
    QString approverid = ui->approverownid->text();        //approver自己的id

    //检查project manager输入
    qDebug()<<recordid;
    qDebug()<<fileid;
    qDebug()<<changereason;
    qDebug()<<changetime;
    qDebug()<<approverid;


    if (recordid=="" ||fileid=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->choooserecordid->clear();
        ui->thefileid->clear();
        ui->changeforwhat->clear();
        ui->thechangedate->clear();
        ui->approverownid->clear();
    }
    else
    {
        QSqlQuery sql;
        sql.prepare("update approvefile set fileid=:fileid , changewhy=:changereason ,changedate=:changetime ,approverid=:approverid where recordid=:recordid");
        sql.bindValue(":recordid",recordid);
        sql.bindValue(":fileid",fileid);
        sql.bindValue(":changereason",changereason);
        sql.bindValue(":changetime",changetime);
        sql.bindValue(":approverid",approverid);


        bool updateIF = sql.exec();
        if(updateIF)
        {
            qDebug()<<"Alter successfully!";
            approverpage::getTableInfo();
            on_pushButton_count_approve_clicked();
        }
        else
        {
            qDebug()<<"Alter failed!";
        }
        approverpage::getTableInfo();//重新获取信息并显示
        sql.clear();
    }
}


void approverpage::on_pushButton_search_clicked()
{
    this->dataTableModel->clear();
    QString id = ui->searchid->text();
    qDebug()<<id;

    if(id == "")
    {
        qDebug()<<"You even don`t keyboard any words！";
        approverpage::setTableinfo();
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("select * from approvefile where recordid=:searchid;");
        sql.bindValue(":searchid",id);
        sql.exec();//执行以上SQL语句
        this->dataTableModel->clear();

        //设置表头
        this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Recordid"));
        this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Fileid"));
        this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Filename"));
        this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Changewhy"));
        this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Changedate"));
        this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("Approverid"));

        //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
        ui->cardTable->setColumnWidth(0,80);
        ui->cardTable->setColumnWidth(1,80);
        ui->cardTable->setColumnWidth(2,100);
        ui->cardTable->setColumnWidth(3,80);
        ui->cardTable->setColumnWidth(4,120);
        ui->cardTable->setColumnWidth(5,80);

        //设置表格只读属性
        ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


        int row = 0;
        while(sql.next())
        {   //将数据库中的表填入表格中
            this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("recordid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("fileid").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("filename").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("changewhy").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("changedate").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("Approverid").toString()));
            row++;
        }
        sql.clear();

        //将设计好的表格模式，装载到表格上
        ui->cardTable->setModel(this->dataTableModel);

    }
}



void approverpage::on_pushButton_logoutapprover_clicked()
{
    this->~approverpage();
    MainWindow * w = new MainWindow();
    w->show();

}





void approverpage::on_pushButton_count_approve_clicked()
{
    QSqlQuery sql;

    sql.prepare("SELECT COUNT(*) FROM approvefile;");  // 统计项目表中的总行数

    bool CountIF = sql.exec();
    if (CountIF)
    {
        sql.next();  // 获取查询结果

        // sql.value(int index)中index是列索引，从0开始
        int count = sql.value(0).toInt();

        qDebug() << "Total rows in project table: " << count;

        //显示行数
        ui->rowcount_approve->setText(QString::number(count));
    }
    else
    {
        qDebug() << "Error COUNT!";
    }
    sql.clear();
}

