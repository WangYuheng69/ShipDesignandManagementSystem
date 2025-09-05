#include "managerpage.h"
#include "ui_managerpage.h"
#include "mainwindow.h"


managerpage::managerpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::managerpage)
{
    ui->setupUi(this);

    //连接数据库
    this->myDatabase.getConnnection();

    qDebug()<<"进入managerpage!";

    //为表格模式指针指定内存
    this->dataTableModel = new QStandardItemModel();

    //设置表格
    // this->setTableinfo();
    ui->controlPage->setCurrentIndex(1);
}

managerpage::~managerpage()
{
    delete ui;
}

void managerpage::setTableinfo()
{
    //设置表头
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Projectid"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Projectname"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Startdate"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Enddate"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Status"));

    //设置表格信息
    this->getTableInfo();

    //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
    ui->cardTable->setColumnWidth(0,80);
    ui->cardTable->setColumnWidth(1,100);
    ui->cardTable->setColumnWidth(2,150);
    ui->cardTable->setColumnWidth(3,150);
    ui->cardTable->setColumnWidth(4,80);

    //设置表格只读属性
    ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //将设计好的表格模式，装载到表格上
    ui->cardTable->setModel(this->dataTableModel);
}

void managerpage::getTableInfo()
{
    //第一步，从数据库中获取信息
    QSqlQuery sql;
    sql.prepare("select * from project");//select from 大小写都行
    sql.exec();

    int row = 0;
    while(sql.next())
    {   //将数据库中的表填入表格中
        this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("projectid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("projectname").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("startdate").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("enddate").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("status").toString()));
        row++;
    }
    sql.clear();
}


//跳到增加位
void managerpage::on_pushButton_add_clicked()
{
    ui->controlPage->setCurrentIndex(0);

    //切换模式清空之前的输入
    ui->setid->clear();
    ui->setname->clear();
    ui->setstart->clear();
    ui->setend->clear();
    ui->setstat->clear();
    // ui->searchname->clear();

    //为表格模式指针指定内存
    //   this->dataTableModle = new QStandardItemModel();
    //设置表格
    this->setTableinfo();
}

//Add！
void managerpage::on_pushButton_addcreate_clicked()
{
    qDebug()<<"add ";
    QString id = ui->setid->text();           //project manager增加的projectid
    QString name = ui->setname->text();       //project manager增加的projectname
    QString start = ui->setstart->text();     //project manager增加的startdate
    QString end = ui->setend->text();         //project manager增加的enddate
    QString stat = ui->setstat->text();       //project manager增加的stat
    //检查用户输入
    qDebug()<<id;
    qDebug()<<name;
    qDebug()<<start;
    qDebug()<<end;
    qDebug()<<stat;

    if (id == "" ||name=="" ||stat=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->setid->clear();
        ui->setname->clear();
        ui->setstart->clear();
        ui->setend->clear();
        ui->setstat->clear();
    }
    else
    {
        QSqlQuery sql;
        sql.prepare("insert into project (projectid,projectname,startdate,enddate,status) values(:id,:name,:start,:end,:stat)");
        sql.bindValue(":id",id);
        sql.bindValue(":name",name);
        sql.bindValue(":start",start);
        sql.bindValue(":end",end);
        sql.bindValue(":stat",stat);


        bool addif = sql.exec();
        if(addif)
        {
            qDebug()<<"增加项目成功！！";
            this->setTableinfo(); // 刷新表格信息
            ui->setid->clear();
            ui->setname->clear();
            ui->setstart->clear();
            ui->setend->clear();
            ui->setstat->clear();
            on_pushButton_count_clicked();  // 刷新总行数
        }
        else
        {
            qDebug()<<"已存在项目！！";
            this->setTableinfo();
            ui->setid->clear();
            ui->setname->clear();
            ui->setstart->clear();
            ui->setend->clear();
            ui->setstat->clear();
            on_pushButton_count_clicked();  // 刷新总行数
        }
        sql.clear();
    }
}



void managerpage::on_pushButton_alter_clicked()
{
    ui->controlPage->setCurrentIndex(1);
    //切换模式清空之前的输入
    ui->chooseid->clear();
    ui->newname->clear();
    ui->newstart->clear();
    ui->newend->clear();
    ui->newstat->clear();
    //设置表格
    this->setTableinfo();
}

//alter!
void managerpage::on_pushButton_altercreate_clicked()
{
    QString id = ui->chooseid->text();        //project manager输入projectid,id肯定不会变
    QString name = ui->newname->text();       //project manager修改的projectname
    QString start = ui->newstart->text();     //project manager修改的startdate
    QString end = ui->newend->text();         //project manager修改的enddate
    QString stat = ui->newstat->text();       //project manager修改的stat

    //检查project manager输入
    qDebug()<<id;
    qDebug()<<name;
    qDebug()<<start;
    qDebug()<<end;
    qDebug()<<stat;

    if (name=="" ||stat=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->chooseid->clear();
        ui->newname->clear();
        ui->newstart->clear();
        ui->newend->clear();
        ui->newstat->clear();
    }
    else
    {
        QSqlQuery sql;
        sql.prepare("update project set projectname=:name ,startdate=:start ,enddate=:end ,status=:stat where projectid=:id");
        sql.bindValue(":id",id);
        sql.bindValue(":name",name);
        sql.bindValue(":start",start);
        sql.bindValue(":end",end);
        sql.bindValue(":stat",stat);

        bool updateIF = sql.exec();
        if(updateIF)
        {
            qDebug()<<"Alter successfully!";
            managerpage::getTableInfo();// 刷新表格信息
            on_pushButton_count_clicked();  // 刷新总行数
        }
        else
        {
            qDebug()<<"Alter failed!";
        }
        managerpage::getTableInfo();//重新获取信息并显示
        sql.clear();
    }
}

void managerpage::on_pushButton_delete_clicked()
{
    ui->controlPage->setCurrentIndex(2);
    //切换模式清空之前的输入
    ui->deleteid->clear();
    ui->deletename->clear();
    ui->deletestatus->clear();
    //设置表格
    this->setTableinfo();
}


void managerpage::on_pushButton_deletecreate_clicked()
{
    QString id = ui->deleteid->text();           //比对project manager选择删除projectid
    QString name = ui->deletename->text();       //比对project manager选择删除projectname
    QString stat = ui->deletestatus->text();     //比对project manager选择删除status
    //检查project manager输入
    qDebug()<<id;
    qDebug()<<name;
    qDebug()<<stat;

    QSqlQuery sql;
    sql.prepare("delete from project where projectid=:deleid and projectname = :delename and status = :delestat");
    sql.bindValue(":deleid",id);
    sql.bindValue(":delename",name);
    sql.bindValue(":delestat",stat);
    bool deleIF = sql.exec();
    if(deleIF)
    {
        qDebug()<<"Delete successfully!";
        managerpage::getTableInfo();    // 刷新表格信息
        on_pushButton_count_clicked();  // 刷新总行数
    }
    else
    {
        qDebug()<<"Delete failed!";
    }
    managerpage::getTableInfo();//重新获取信息并显示
    sql.clear();
}



void managerpage::on_pushButton_search_clicked()
{
    this->dataTableModel->clear();
    QString id = ui->searchid->text();
    qDebug()<<id;

    if(id == "")
    {
        qDebug()<<"You even don`t keyboard any words！";
        managerpage::setTableinfo();
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("select * from project where projectid=:searchid;");
        sql.bindValue(":searchid",id);
        sql.exec();//执行以上SQL语句
        this->dataTableModel->clear();

        //设置表头
        this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Projectid"));
        this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Projectname"));
        this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Startdate"));
        this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Enddate"));
        this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Status"));

        //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
        ui->cardTable->setColumnWidth(0,80);
        ui->cardTable->setColumnWidth(1,100);
        ui->cardTable->setColumnWidth(2,150);
        ui->cardTable->setColumnWidth(3,150);
        ui->cardTable->setColumnWidth(4,80);

        //设置表格只读属性
        ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


        int row = 0;
        while(sql.next())
        {   //将数据库中的表填入表格中
            this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("projectid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("projectname").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("startdate").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("enddate").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("status").toString()));
            row++;
        }
        sql.clear();

        //将设计好的表格模式，装载到表格上
        ui->cardTable->setModel(this->dataTableModel);

    }
}


void managerpage::on_pushButton_logout_clicked()
{
    this->~managerpage();
    MainWindow * w = new MainWindow();
    w->show();

}





void managerpage::on_pushButton_count_clicked()
{
    QSqlQuery sql;

    sql.prepare("SELECT COUNT(*) FROM project;");  // 统计项目表中的总行数

    bool CountIF = sql.exec();
    if (CountIF)
    {
        sql.next();  // 获取查询结果

        // sql.value(int index)中index是列索引，从0开始
        int count = sql.value(0).toInt();

        qDebug() << "Total rows in project table: " << count;

        //显示行数
        ui->rowcount_project->setText(QString::number(count));
    }
    else
    {
        qDebug() << "Error COUNT!";
    }
    sql.clear();

}

