#include "change_inf.h"
#include "ui_change_inf.h"
#include <QString>
#include "mainwindow.h"
#include <QDebug>

change_inf::change_inf(int i,QString no,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change_inf)
{
    ui->setupUi(this);
    option = i;
    cur_no = no;
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

change_inf::~change_inf()
{
    delete ui;
}

void change_inf::on_pushButton_clicked()
{
    QString password = ui->lineEdit_2->text();
    QString password_2 = ui->lineEdit_3->text();
    QString password_old = ui->lineEdit->text();
    if(password != password_2)
    {
        QMessageBox::warning(NULL,"Warning","两次输入的密码不一致",QMessageBox::Ok);
        return;
    }

    model = new QSqlTableModel;
    if(option == 1)
    {
        model->setTable("manager");
        model->setFilter(QObject::tr("maccount=\'%1\'").arg(cur_no));
        model->setSort(0,Qt::AscendingOrder);
        model->select();
    }
    else if(option == 2)
    {
        model->setTable("staff");
        model->setFilter(QObject::tr("sno=\'%1\'").arg(cur_no));
        model->setSort(0,Qt::AscendingOrder);
        model->select();
    }
    else
    {
        qDebug() << "change_inf::on_pushButton_clicked error";
        return ;
    }

    if(model->rowCount()==0)
    {
        qDebug() << "change_inf::on_pushButton_clicked error";
        return ;
    }
    else
    {
        QString old_psw_intable;
        if(option ==1)
        {
            old_psw_intable = model->record(0).value("mpsw").toString();
        }
        else
        {
            old_psw_intable = model->record(0).value("spsw").toString();
        }
        if(old_psw_intable != password_old)
        {
            QMessageBox::warning(NULL,"Warning","原密码输入有误",QMessageBox::Ok);
            return;
        }
        QSqlRecord record = model->record(0);
        if(option ==1)
            record.setValue("mpsw",password);
        else
            record.setValue("spsw",password);
        model->setRecord(0,record);
        model->submitAll();
        QMessageBox::about(NULL,"ok","修改密码成功!");
        this->close();
        return;
    }

}

void change_inf::on_pushButton_2_clicked()
{
    this->close();
}
