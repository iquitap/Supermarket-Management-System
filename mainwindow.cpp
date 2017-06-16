#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//#include "saleman.h"

saleman *windows_saleman;
manager *windows_manager;
goodsman *windows_goodsman;
QSqlDatabase db;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    /*db = QSqlDatabase::addDatabase("QMYSQL");
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
    }*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool is_manager = ui->radioButton_manager->isChecked();
    bool is_saleman = ui->radioButton_saleman->isChecked();
    bool is_goodsman = ui->radioButton_goodsman->isChecked();
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    qDebug() << is_manager <<  " " << is_saleman << " " << is_goodsman;

    if(!(is_manager || is_saleman || is_goodsman))
    {
        QMessageBox::information(NULL, tr("Warning"), tr("请选择你的登陆身份"));
        return ;
    }
    else if(is_manager)
    {
        QSqlQuery query;
        bool success = query.exec("select * from MANAGER");
        if(!success){
         qDebug() << "查询manager失败";;
        }
        QSqlRecord rec = query.record();
        qDebug() << "manager表的字段总数为：" << rec.count();
        query.first();;
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() ;
        qDebug() << "show_table_manager end.";
        bool flag = query.value(0).toString() == username && query.value(1).toString() == password;
        if(flag)
        {
            windows_manager = new manager(query.value(0).toString());
            windows_manager->show();
            this->close();
            qDebug() << "manager login success!";
        }
        else
        {
            qDebug() << username << query.value(0).toString() ;
            qDebug() << password << query.value(1).toString() ;
            QMessageBox::information(NULL,tr("Warning"), tr("Username or password is wrong."));
        }
    }
    else if(is_saleman)
    {
        QSqlQuery query;
        bool success = query.exec("select saccount,spsw,sno from staff where spart = \"sale\";");
        if(!success){
         qDebug() << "查询saleman失败";;
        }
        QSqlRecord rec = query.record();
        qDebug() << "saleman表的字段总数为：" << rec.count();
        // 将查询的结果集指针调整到最开始
        query.seek(-1);
        bool flag = false;
        while(query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() ;
            if(query.value(0).toString() == username && query.value(1).toString() == password)
            {
                flag = true;
                break;
            }
        }
        qDebug() << "show_table_saleman end.";
        if(flag)
        {
            windows_saleman = new saleman(query.value(2).toString());
            windows_saleman->show();
            this->close();
            qDebug() << "staff login success!";
        }
        else
        {
            qDebug() << username << query.value(0).toString() ;
            qDebug() << password << query.value(1).toString() ;
            QMessageBox::information(NULL,tr("Warning"), tr("Username or password is wrong."));
        }

    }
    else if(is_goodsman)
    {
        QSqlQuery query;
        bool success = query.exec("select saccount,spsw,sno from staff where spart = \"goods\";");
        if(!success){
         qDebug() << "查询goodsman失败";;
        }
        QSqlRecord rec = query.record();
        qDebug() << "goodsman表的字段总数为：" << rec.count();
        // 将查询的结果集指针调整到最开始
        query.seek(-1);
        bool flag = false;
        while(query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() ;
            if(query.value(0).toString() == username && query.value(1).toString() == password)
            {
                flag = true;
                break;
            }
        }
        qDebug() << "show_table_goodsman end.";
        if(flag)
        {
            windows_goodsman = new goodsman(query.value(2).toString());
            windows_goodsman->show();
            this->close();
            qDebug() << "staff login success!";
        }
        else
        {
            qDebug() << username << query.value(0).toString() ;
            qDebug() << password << query.value(1).toString() ;
            QMessageBox::information(NULL,tr("Warning"), tr("Username or password is wrong."));
        }
    }
}

void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}
