#ifndef MANAGERPAGE_H
#define MANAGERPAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <database.h>
#include <QStandardItemModel>



namespace Ui {
class managerpage;
}

class managerpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit managerpage(QWidget *parent = nullptr);
    ~managerpage();

    //连接数据库的对象
    database myDatabase;

    //设置表格格式
    void setTableinfo();

    //获取表格信息
    void getTableInfo();

    //表格组件模式
    QStandardItemModel * dataTableModel;

private slots:


    void on_pushButton_addcreate_clicked();

    void on_pushButton_add_clicked();


    void on_pushButton_altercreate_clicked();

    void on_pushButton_alter_clicked();

    void on_pushButton_deletecreate_clicked();


    void on_pushButton_search_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_count_clicked();

private:
    Ui::managerpage *ui;

};

#endif // MANAGERPAGE_H
