#include "designerpage.h"
#include "ui_designerpage.h"
#include "mainwindow.h"

designerpage::designerpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::designerpage)
{
    ui->setupUi(this);

    //连接数据库
    this->myDatabase.getConnnection();

    qDebug()<<"进入designerpage!";

    //为表格模式指针指定内存
    this->dataTableModel = new QStandardItemModel();
    //注意是controlPage_2(ui里取得名字，必须得对应，不然pushbutton没反应
    ui->controlPage_2->setCurrentIndex(1);
}

designerpage::~designerpage()
{
    delete ui;
}


void designerpage::setTableinfo()
{
    //设置表头
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Fileid"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Filename"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Filetype"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Uploaddate"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Versionnumber"));
    this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("Designerid"));
    this->dataTableModel->setHorizontalHeaderItem(6,new QStandardItem("Projectid"));
\
    //设置表格信息
    this->getTableInfo();

    //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
    ui->cardTable->setColumnWidth(0,80);
    ui->cardTable->setColumnWidth(1,100);
    ui->cardTable->setColumnWidth(2,80);
    ui->cardTable->setColumnWidth(3,120);
    ui->cardTable->setColumnWidth(4,50);
    ui->cardTable->setColumnWidth(5,80);
    ui->cardTable->setColumnWidth(6,80);

    //设置表格只读属性
    ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //将设计好的表格模式，装载到表格上
    ui->cardTable->setModel(this->dataTableModel);
}

void designerpage::getTableInfo()
{
    //第一步，从数据库中获取信息
    QSqlQuery sql;
    sql.prepare("select * from designfile");//select from 大小写都行
    sql.exec();

    int row = 0;
    while(sql.next())
    {   //将数据库中的表填入表格中
        this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("fileid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("filename").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("filetype").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("uploaddate").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("versionnumber").toString()));
        this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("designerid").toString()));
        this->dataTableModel->setItem(row,6,new QStandardItem(sql.value("projectid").toString()));
        row++;
    }
    sql.clear();
}


//add的button
void designerpage::on_pushButton_add_file_clicked()
{
    ui->controlPage_2->setCurrentIndex(0);

    //切换模式清空之前的输入
    ui->setfileid->clear();
    ui->setfilename->clear();
    ui->setfiletype->clear();
    ui->setdate->clear();
    ui->setversion->clear();
    ui->thedesignerid->clear();
    ui->theprojectid->clear();
    //设置表格
    this->setTableinfo();
}



//Add！
void designerpage::on_pushButton_addcreate_file_clicked()
{
    qDebug()<<"add file";
    QString fileidadd = ui->setfileid->text();           //designer 增加的setfileid
    QString nameadd = ui->setfilename->text();           //designer 增加的setfilename
    QString typeadd = ui->setfiletype->text();           //designer 增加的setfiletype
    QString dateadd = ui->setdate->text();               //designer 增加的setdate
    QString versionadd = ui->setversion->text();         //designer 增加的setversion
    QString designerid_add = ui->thedesignerid->text();  //designer 的id
    QString projectid_add = ui->theprojectid->text();    //项目的id
    //检查用户输入
    qDebug()<<fileidadd;
    qDebug()<<nameadd;
    qDebug()<<typeadd;
    qDebug()<<dateadd;
    qDebug()<<versionadd;
    qDebug()<<designerid_add;
    qDebug()<<projectid_add;

    if (fileidadd == "" ||nameadd=="" )
    {
        qDebug()<<"不能为空请重新输入";
        ui->setfileid->clear();
        ui->setfilename->clear();
        ui->setfiletype->clear();
        ui->setdate->clear();
        ui->setversion->clear();
        ui->thedesignerid->clear();
        ui->theprojectid->clear();
    }
    else
    {
        QSqlQuery sql;
        //upload打错了，debug半天！！！
        // qDebug()<<"成功？";
        sql.prepare("insert into designfile (fileid,filename,filetype,uploaddate,versionnumber,designerid,projectid) values(:fileid_1,:name,:type,:date,:version,:designerid,:projectid)");
        sql.bindValue(":fileid_1",fileidadd);
        sql.bindValue(":name",nameadd);
        sql.bindValue(":type",typeadd);
        sql.bindValue(":date",dateadd);
        sql.bindValue(":version",versionadd);
        sql.bindValue(":designerid",designerid_add);//designerid达成designid，死活没找出来，然后也debug了半天
        sql.bindValue(":projectid",projectid_add);

        // qDebug()<<"成没成功？";
        bool addif = sql.exec();
        if(addif)
        {
            qDebug()<<"新增设计文件成功！！";
            this->setTableinfo();
            ui->setfileid->clear();
            ui->setfilename->clear();
            ui->setfiletype->clear();
            ui->setdate->clear();
            ui->setversion->clear();
            ui->thedesignerid->clear();
            ui->theprojectid->clear();
            on_pushButton_count_file_clicked();
        }
        else
        {
            qDebug()<<"已存在此文件！！";
            this->setTableinfo();
            ui->setfileid->clear();
            ui->setfilename->clear();
            ui->setfiletype->clear();
            ui->setdate->clear();
            ui->setversion->clear();
            ui->thedesignerid->clear();
            ui->theprojectid->clear();
            on_pushButton_count_file_clicked();
        }
        sql.clear();
    }
}

//alter的button
void designerpage::on_pushButton_alter_file_clicked()
{
    ui->controlPage_2->setCurrentIndex(1);
    //切换模式清空之前的输入
    ui->choosefileid->clear();
    ui->newfilename->clear();
    ui->newtype->clear();
    ui->newdate->clear();
    ui->newversion->clear();
    ui->thedesignerid_2->clear();
    ui->theprojectid_2->clear();
    //设置表格
    this->setTableinfo();
}


//alter!
void designerpage::on_pushButton_altercreate_file_clicked()
{
    QString fileid_2 = ui->choosefileid->text();          //designer 输入fileid
    QString name_2 = ui->newfilename->text();             //designer 修改的name
    QString type_2 = ui->newtype->text();                 //designer 修改的type
    QString date_2 = ui->newdate->text();                 //designer 修改的date
    QString version_2 = ui->newversion->text();           //designer 修改的version
    QString designerid_2 = ui->thedesignerid_2->text();   //designer自己的id
    QString projectid_2 = ui->theprojectid_2->text();     //项目的id

    //检查designer输入
    qDebug()<<fileid_2;
    qDebug()<<name_2;
    qDebug()<<type_2;
    qDebug()<<date_2;
    qDebug()<<version_2;
    qDebug()<<designerid_2;
    qDebug()<<projectid_2;

    if (name_2==""||fileid_2=="")
    {
        qDebug()<<"不能为空请重新输入";
        ui->choosefileid->clear();
        ui->newfilename->clear();
        ui->newtype->clear();
        ui->newdate->clear();
        ui->newversion->clear();
        ui->thedesignerid_2->clear();
        ui->theprojectid_2->clear();
    }
    else
    {
        QSqlQuery sql;
        //qDebug()<<"成功？";
        //多写了一个type!debug...
        sql.prepare("update designfile set filename=:name_2 ,filetype=:type_2 ,uploaddate=:date_2 ,versionnumber=:version_2 ,designerid=:designerid_2 ,projectid=:projectid_2 where fileid=:fileid_2");
        sql.bindValue(":fileid_2",fileid_2);
        sql.bindValue(":name_2",name_2);
        sql.bindValue(":type_2",type_2);
        sql.bindValue(":date_2",date_2);
        sql.bindValue(":version_2",version_2);
        sql.bindValue(":designerid_2",designerid_2);
        sql.bindValue(":projectid_2",projectid_2);

        qDebug()<<"chenggong?";

        bool updateIF = sql.exec();
        if(updateIF)
        {
            qDebug()<<"Alter successfully!";
            designerpage::getTableInfo();
            on_pushButton_count_file_clicked();
        }
        else
        {
            qDebug()<<"Alter failed!";
        }
        designerpage::getTableInfo();//重新获取信息并显示
        sql.clear();
    }
}


//delete的button
void designerpage::on_pushButton_deletefile_clicked()
{
    ui->controlPage_2->setCurrentIndex(2);
    //切换模式清空之前的输入
    ui->deleteid_file->clear();
    ui->deletename_file->clear();
    ui->thedesignerid_3->clear();
    ui->theprojectid_3->clear();
    //设置表格
    this->setTableinfo();
}


//delete！
void designerpage::on_pushButton_deletecreate_file_clicked()
{
    QString fileid_3 = ui->deleteid_file->text();           //比对designer选择删除的fileid
    QString name_3 = ui->deletename_file->text();           //比对designer选择删除的filename
    QString designerid_3 = ui->thedesignerid_3->text();     //确保人员正确
    QString projectid_3 = ui->theprojectid_3->text();       //确保项目正确

    //检查project manager输入
    qDebug()<<fileid_3;
    qDebug()<<name_3;
    qDebug()<<designerid_3;
    qDebug()<<projectid_3;

    QSqlQuery sql;
    sql.prepare("delete from designfile where fileid=:deleid and filename = :delename and designerid = :designerid_3 and projectid = :projectid_3");
    sql.bindValue(":deleid",fileid_3);
    sql.bindValue(":delename",name_3);
    sql.bindValue(":designerid_3",designerid_3);
    sql.bindValue(":projectid_3",projectid_3);
    bool deleIF = sql.exec();
    if(deleIF)
    {
        qDebug()<<"Delete successfully!";
        this->setTableinfo();
        ui->deleteid_file->clear();
        ui->deletename_file->clear();
        ui->thedesignerid_3->clear();
        ui->theprojectid_3->clear();
        on_pushButton_count_file_clicked();
    }
    else
    {
        qDebug()<<"Delete failed!";
    }
    sql.clear();
}


//search！
void designerpage::on_pushButton_search_file_clicked()
{
    this->dataTableModel->clear();
    QString id = ui->searchid_file->text();
    qDebug()<<id;

    if(id == "")
    {
        qDebug()<<"You even don`t keyboard any words！";
        designerpage::setTableinfo();
    }
    else
    {
        QSqlQuery sql;

        sql.prepare("select * from designfile where fileid=:searchfileid;");
        sql.bindValue(":searchfileid",id);
        sql.exec();//执行以上SQL语句
        this->dataTableModel->clear();

        //设置表头
        this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("Fileid"));
        this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("Filename"));
        this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("Filetype"));
        this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("Uploaddate"));
        this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("Versionnumber"));
        this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("Designerid"));
        this->dataTableModel->setHorizontalHeaderItem(6,new QStandardItem("Projectid"));

        //设置列宽,cardTable为ui设计Table View的名字（当然在ui中也可以直接拖动，改变列宽）
        ui->cardTable->setColumnWidth(0,80);
        ui->cardTable->setColumnWidth(1,100);
        ui->cardTable->setColumnWidth(2,80);
        ui->cardTable->setColumnWidth(3,120);
        ui->cardTable->setColumnWidth(4,50);
        ui->cardTable->setColumnWidth(5,80);
        ui->cardTable->setColumnWidth(6,80);

        //设置表格只读属性
        ui->cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


        int row = 0;
        while(sql.next())
        {   //将数据库中的表填入表格中
            this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("fileid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("filename").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("filetype").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("uploaddate").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("versionnumber").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("designerid").toString()));
            this->dataTableModel->setItem(row,6,new QStandardItem(sql.value("projectid").toString()));
            row++;
        }
        sql.clear();

        //将设计好的表格模式，装载到表格上
        ui->cardTable->setModel(this->dataTableModel);

    }
}



//log out的button
void designerpage::on_pushButton_logout_file_clicked()
{
    this->~designerpage();
    MainWindow * w = new MainWindow();
    w->show();
}





void designerpage::on_pushButton_count_file_clicked()
{
    QSqlQuery sql;

    sql.prepare("SELECT COUNT(*) FROM designfile;");  // 统计项目表中的总行数

    bool CountIF = sql.exec();
    if (CountIF)
    {
        sql.next();  // 获取查询结果

        // sql.value(int index)中index是列索引，从0开始
        int count = sql.value(0).toInt();

        qDebug() << "Total rows in project table: " << count;

        //显示行数
        ui->rowcount_file->setText(QString::number(count));
    }
    else
    {
        qDebug() << "Error COUNT!";
    }
    sql.clear();
}

