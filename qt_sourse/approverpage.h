#ifndef APPROVERPAGE_H
#define APPROVERPAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <database.h>
#include <QStandardItemModel>


namespace Ui {
class approverpage;
}

class approverpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit approverpage(QWidget *parent = nullptr);
    ~approverpage();

    //连接数据库的对象
    database myDatabase;

    //设置表格格式
    void setTableinfo();

    //获取表格信息
    void getTableInfo();

    //表格组件模式
    QStandardItemModel * dataTableModel;

private slots:

    void on_pushButton_approvealter_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_logoutapprover_clicked();

    void on_pushButton_count_approve_clicked();

private:
    Ui::approverpage *ui;
};

#endif // APPROVERPAGE_H
