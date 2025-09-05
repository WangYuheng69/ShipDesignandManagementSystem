#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include <managerpage.h>
#include <designerpage.h>
#include <approverpage.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    database::getConnnection();
    //database::quitConnection();

    MainWindow w;
    //managerpage w;
    // designerpage  w;
    //approverpage w;
    w.show();
    return a.exec();

}
