#ifndef DESIGNERPAGE_H
#define DESIGNERPAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <database.h>
#include <QStandardItemModel>


namespace Ui {
class designerpage;
}

class designerpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit designerpage(QWidget *parent = nullptr);
    ~designerpage();

    //连接数据库的对象
    database myDatabase;

    //设置表格格式
    void setTableinfo();

    //获取表格信息
    void getTableInfo();

    //表格组件模式
    QStandardItemModel * dataTableModel;

private slots:

    void on_pushButton_logout_file_clicked();

    void on_pushButton_add_file_clicked();

    void on_pushButton_addcreate_file_clicked();

    void on_pushButton_alter_file_clicked();

    void on_pushButton_altercreate_file_clicked();

    void on_pushButton_deletefile_clicked();

    void on_pushButton_deletecreate_file_clicked();

    void on_pushButton_search_file_clicked();

    void on_pushButton_count_file_clicked();

private:
    Ui::designerpage *ui;
};

#endif // DESIGNERPAGE_H
