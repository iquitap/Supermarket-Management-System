#include "goodsman.h"
#include "ui_goodsman.h"
#include "mainwindow.h"
#include <QDebug>
#include "change_inf.h"

change_inf * windows_change_inf3;
MainWindow * windows_main3;
goodsman::goodsman(QString sno,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::goodsman)
{
    ui->setupUi(this);
    cur_goodsman_no = sno;
}

goodsman::~goodsman()
{
    delete ui;
}

void goodsman::on_pushButton_clicked()
{
    windows_main3 = new MainWindow();
    windows_main3->show();
    this->close();
}


void goodsman::on_pushButton_import_clicked()
{
    QString gno = ui->lineEdit->text();
    int amount = ui->spinBox_stock->value();
    model = new QSqlTableModel;
    model->setTable("GOODS");
    model->setFilter(QObject::tr("gno=\'%1\'").arg(gno));
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    if(model->rowCount()==0)
    {
        QMessageBox::warning(NULL,"Warning","该商品不存在",QMessageBox::Ok);
        return;
    }
    QSqlRecord record = model->record(0);
    record.setValue("gstock",record.value("gstock").toInt()+amount);
    model->setRecord(0,record);
    if(model->submitAll())
        QMessageBox::warning(NULL,"Message","进货成功",QMessageBox::Ok);
    else
        QMessageBox::warning(NULL,"Message","进货失败",QMessageBox::Ok);

    ui->lineEdit->setText("");
    ui->lineEdit_stock->setText("");
    ui->spinBox_stock->setValue(0);
}

void goodsman::on_pushButton_stock_clicked()
{
    QString gno = ui->lineEdit->text();
    model = new QSqlTableModel;
    model->setTable("GOODS");
    model->setFilter(QObject::tr("gno=\'%1\'").arg(gno));
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    if(model->rowCount()==0)
    {
        QMessageBox::warning(NULL,"Warning","该商品不存在",QMessageBox::Ok);
        return;
    }
    QString stock = model->record(0).value(2).toString();
    ui->lineEdit_stock->setText(stock);
    qDebug() << "stock: " << stock;
}

void goodsman::on_pushButton_5_clicked()
{
    windows_change_inf3 = new change_inf(2,cur_goodsman_no);
    windows_change_inf3->show();
}
