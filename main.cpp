#include "mainwindow.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //QSqlDatabase db = QSqlDatabase::database();
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("supermarket");
    db.setUserName("root");
    db.setPassword("");
    if(db.open())
    {
      qDebug()<<"success!";
    }else{
      qDebug()<<"failure";
    }

    return a.exec();
}
