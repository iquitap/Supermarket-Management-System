#include "saleman.h"
#include "ui_saleman.h"
#include "mainwindow.h"
#include <qmessagebox.h>
#include <QInputDialog>
#include "change_inf.h"

change_inf * windows_change_inf2;
MainWindow * windows_main;
saleman::saleman(QString sno,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::saleman)
{
    ui->setupUi(this);
    all_1 = 0;all_2=0;all_3=0;
    ui->label_cashier_all1->setText("现金总计: "+QString::number(all_1));
    ui->label_cashier_all2->setText("会员卡总计: "+QString::number(all_2));
    ui->label_cashier_all3->setText("办卡金额总计: "+QString::number(all_3));

    sale_initial();
    cur_salesman_no = sno;
}

saleman::~saleman()
{
    delete ui;
}

void saleman::on_pushButton_cashier_exit_clicked()
{
    windows_main = new MainWindow();
    windows_main->show();
    this->close();
}

void saleman::on_pushButton_cashier_exit_2_clicked()
{
    windows_main = new MainWindow();
    windows_main->show();
    this->close();
}

void saleman::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        sale_initial();
        break;
    case 1:
        card_initial();
        break;
    default:
        break;
    }
}

QString saleman::get_new_sano()
{
    QSqlTableModel *model_temp = new QSqlTableModel;
    model_temp->setTable("sale");
    model_temp->setSort(0,Qt::AscendingOrder);
    model_temp->select();
    QString sano;

    for(int i=1;i<=9999;i++)
    {
        sano="o"+ToStr(i,4);
        model_temp->setFilter(QObject::tr("sano=\'%1\'").arg(sano));
        if(model_temp->rowCount()==0)
            break;
    }
    return sano;
}

void saleman::card_initial()
{
    qDebug() << "card_initial";
    model = new QSqlTableModel;
    model->setTable("CARD");
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    QString cno;
    current_date_time = QDateTime::currentDateTime();
    QDateTime deadline = current_date_time.addYears(1);
    for(int i=1;i<=9999;i++)
    {
        cno="c"+ToStr(i,4);
        model->setFilter(QObject::tr("cno=\'%1\'").arg(cno));
        if(model->rowCount()==0)
            break;
    }
    ui->lineEdit_name->setText("");
    ui->lineEdit_phone->setText("");
    ui->lineEdit_cno->setText(cno);
    ui->lineEdit_money->setText("100");
    ui->lineEdit_date->setText(deadline.toString("yyyy-MM-dd"));
}

void saleman::on_pushButton_clicked()
{
    QString cname =ui->lineEdit_name->text();
    QString cphone=ui->lineEdit_phone->text();
    QString cdl=ui->lineEdit_date->text();
    QString cno=ui->lineEdit_cno->text();
    QString cmoney=ui->lineEdit_money->text();
    QDateTime copendata = current_date_time;
    if(cname==""|| cphone=="")
    {
        QMessageBox::warning(NULL, "Warning", "开卡人信息不能为空", QMessageBox::Ok);
        return;
    }
    QSqlQuery query;
    int value=query.exec(QObject::tr("insert into card values "
    "('%1','%2',0,'%3','%4','%5','%6')").arg(cno,cmoney,copendata.toString("yyyy-MM-dd"),cdl,cname,cphone));
    if(value)
    {
        all_3 += cmoney.toFloat();
        QMessageBox::warning(NULL,"Message","办卡成功",QMessageBox::Ok);
        ui->label_cashier_all3->setText("办卡金额总计: "+QString::number(all_3));
    }
    else
        QMessageBox::warning(NULL,"Warning","办卡失败",QMessageBox::Ok);

    card_initial();
}


void saleman::sale_initial()
{
    qDebug() << "sale_initial";

    cashier_total_money = 0;
    cashier_total_amount = 0;
    cur_card_no = "00000";

    int rows = ui->tableWidget_cashier->rowCount();
    for(int i=rows-1;i>=0;i--)
        ui->tableWidget_cashier->removeRow(i);
    ui->lineEdit_cashier_gno->clear();
    ui->spinBox_cashier_amount->setValue(0);
    ui->textBrowser_goods_amount->clear();
    ui->textBrowser_cashier_total_money->clear();
    ui->radioButton_usecard->setChecked(false);
    ui->lineEdit_cashier_cno->clear();
    ui->textBrowser_cashier_cmoney->clear();


}

void saleman::on_pushButton_cashier_add_clicked()       //添加商品
{
    QString gno = ui->lineEdit_cashier_gno->text();
    int amount =ui->spinBox_cashier_amount->value();
    if(amount==0)
    {
        QMessageBox::warning(NULL,"Warning","请输入商品数量",QMessageBox::Ok);
        return;
    }
    model = new QSqlTableModel;
    model->setTable("goods");
    model->setFilter(QObject::tr("gno=\'%1\'").arg(gno));
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    if(model->rowCount()==0)
    {
        QMessageBox::warning(NULL,"Warning","该商品不存在",QMessageBox::Ok);
        return;
    }
    else if(model->record(0).value("gstock")<amount)
    {
        QMessageBox::warning(NULL,"Warning","库存不足",QMessageBox::Ok);
        return;
    }
    QString gname = model->record(0).value("gname").toString();
    QString gprice_str = model->record(0).value("gprice").toString();
    double money = (double)amount * gprice_str.toDouble();

    //计算总金额
    cashier_total_money += money;
    cashier_total_amount += amount;
    ui->textBrowser_cashier_total_money->setText(QString::number(cashier_total_money));
    ui->textBrowser_goods_amount->setText(QString::number(cashier_total_amount));
    ui->tableWidget_cashier->insertRow(0);
    ui->tableWidget_cashier->setItem(0,0,new QTableWidgetItem(gno));
    ui->tableWidget_cashier->setItem(0,1,new QTableWidgetItem(gname));
    ui->tableWidget_cashier->setItem(0,2,new QTableWidgetItem(gprice_str));
    ui->tableWidget_cashier->setItem(0,3,new QTableWidgetItem(QString::number(amount)));
    ui->tableWidget_cashier->setItem(0,4,new QTableWidgetItem(QString::number(money)));
    ui->lineEdit_cashier_gno->setText("");
    ui->spinBox_cashier_amount->setValue(0);
}

void saleman::on_pushButton_cashier_delete_clicked()    //删除商品
{
    int rowIndex = ui->tableWidget_cashier->currentRow();
    if (rowIndex != -1)
    {
        QString amount_str = ui->tableWidget_cashier->item(rowIndex,3)->text();
        QString money_str = ui->tableWidget_cashier->item(rowIndex,4)->text();
        cashier_total_amount -= amount_str.toInt();
        cashier_total_money -= money_str.toDouble();
        ui->tableWidget_cashier->removeRow(rowIndex);
    }
    else
    {
        QMessageBox::warning(NULL,"Warning","请选中要删除的商品",QMessageBox::Ok);
        return;
    }

}

//检查当前会员是否过期，并做相应操作
bool saleman::check_account(QString cno)
{
    model = new QSqlTableModel;
    model->setTable("card");
    model->setFilter(QObject::tr("cno=\'%1\'").arg(cno));
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    QDate deadline = model->record(0).value("cdeadline").toDate();
    double cremoney = model->record(0).value("cremoney").toDouble();

    //过期
    if(deadline<QDate::currentDate())
    {
        QString text = QInputDialog::getText(NULL, "Warning",
                                                "该卡号已过期,请输入续费金额",
                                                QLineEdit::Normal,          //输入框明文
                                                NULL);

        if(text.toDouble() > 0)
        {
            /*QSqlQuery query;
            query.exec(QObject::tr("insert into sale values "
                                   "('00000','g0000','%1',1,'%2','%3')")
                       .arg(current_date_time.toString("yyyy-MM-dd hh:mm:ss"),cur_salesman_no));*/


            deadline = QDate::currentDate().addYears(2);
            QSqlRecord record = model->record(0);
            //重置有效期和余额
            record.setValue("cdeadline",deadline.toString("yyyy-MM-dd"));
            record.setValue("cremoney",cremoney+text.toDouble());
            model->setRecord(0,record);
            model->submitAll();

            return true;
        }
        //不续费
        else
        {
            model->submitAll();
            qDebug()<<"不续费";
            return false;
        }
    }
    else
    {
        if(cremoney < cashier_total_money)
        {
            qDebug() << "cremoney = " << cremoney;
            qDebug() << "cashier_total_money = " << cashier_total_money;
            QString text = QInputDialog::getText(NULL, "Warning",
                                                    "卡内余额不足,请输入续费金额",
                                                    QLineEdit::Normal,          //输入框明文
                                                    NULL);
            if(text.toDouble() + cremoney > cashier_total_money && text.toDouble() > 0)
            {
                QSqlRecord record = model->record(0);
                record.setValue("cremoney",cremoney+text.toDouble());
                record.setValue("cdeadline",QDate::currentDate().addYears(2));
                model->setRecord(0,record);
                model->submitAll();
                return true;
            }
            else
            {
                QMessageBox::about(NULL,"warning","充值之后余额依旧不足，改用现金付款");
                return false;
            }
        }
    }
    return true;
}

void saleman::on_pushButton_cashier_settle_clicked()    //结账
{
    QString cremonry_str;
    cashier_satype = ui->radioButton_usecard->isChecked();
    QString cno = ui->lineEdit_cashier_cno->text();
    if(cashier_satype)      //卡结账
    {
        model = new QSqlTableModel;
        model->setTable("card");
        model->setFilter(QObject::tr("cno=\'%1\'").arg(cno));
        model->setSort(0,Qt::AscendingOrder);
        model->select();
        if(model->rowCount()==0)    //找卡失败
        {
            QMessageBox::warning(NULL,"Warning","该卡号不存在",QMessageBox::Ok);
            sale_initial();
            return ;
        }
        else
        {
            cremonry_str = model->record(0).value("cremoney").toString();
            ui->textBrowser_cashier_cmoney->setText(cremonry_str);
            if(check_account(cno))
                cur_card_no = cno;
            else            //卡内余额不足或者卡过期
            {
                cashier_satype = false;
                cur_card_no = "00000";
            }
        }
    }

    if(cur_card_no!="00000")   //会员9折
    {
        qDebug() << cur_card_no;
        cashier_total_money *= 0.9;
    }
    QSqlQuery query;
    int rowCount = ui->tableWidget_cashier->rowCount();
    //开启数据库事务
    QSqlDatabase::database().transaction();
    //生成订单，修改库存
    for(int i=0;i<rowCount;i++)
    {
        current_date_time = QDateTime::currentDateTime();
        QString sano = get_new_sano();
        QString gno = ui->tableWidget_cashier->item(i,0)->text();
        QString gname = ui->tableWidget_cashier->item(i,1)->text();
        int amount = ui->tableWidget_cashier->item(i,3)->text().toInt();
        double money = ui->tableWidget_cashier->item(i,4)->text().toDouble();
        qDebug()<<sano<<((cashier_satype==true)?"true":"false")<<cur_card_no<<gname<<amount<<money<<current_date_time.toString("yyyy-MM-dd hh:mm:ss");

        //int value = query.exec(QObject::tr("insert into sale values ('%1','false','00000','g0000','%2',1,'%2','%3')").arg(get_new_sano(),current_date_time.toString("yyyy-MM-dd hh:mm:ss"),text.toDouble() ,cur_salesman_no));
        int value0 = query.exec(QObject::tr("select * from goods"));
        int value1 = query.exec(QObject::tr("select * from goodgood"));
        int value = query.exec(QObject::tr("insert into sale values "
                                "('%1',%2,'%3','%4','%5',%6,%7,'%8')")
                                .arg(sano)
                                .arg((cashier_satype==true)?true:false)
                                .arg(cur_card_no)
                                .arg(gno)
                                .arg(current_date_time.toString("yyyy-MM-dd hh:mm:ss"))
                                .arg(amount)
                                .arg(cur_card_no=="00000" ? money : money * 0.9)
                                .arg(cur_salesman_no));

        qDebug() << value0 << value1 << value;
        if(!value)
        {
            //有一条订单插入失败则事务执行失败，回滚
            QMessageBox::warning(NULL,"Warning","收银失败",QMessageBox::Ok);
            QSqlDatabase::database().rollback();
            sale_initial();
            return;
        }
    }
    QSqlDatabase::database().commit();

    model = new QSqlTableModel;
    model->setTable("card");
    model->setFilter(QObject::tr("cno=\'%1\'").arg(cur_card_no));
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    cremonry_str = model->record(0).value("cremoney").toString();
    if(cur_card_no!="00000")
        ui->textBrowser_cashier_cmoney->setText(cremonry_str);
    QMessageBox::information(NULL,"提示","收银成功,一共消费"+QString::number(cashier_total_money)+"元",QMessageBox::Ok);
    if(cur_card_no!="00000")
    {
        all_2 += cashier_total_money;
    }
    else
        all_1 += cashier_total_money;
    ui->label_cashier_all1->setText("现金总计: "+QString::number(all_1));
    ui->label_cashier_all2->setText("会员卡总计: "+QString::number(all_2));
    sale_initial();
}


void saleman::on_pushButton_cashier_settle_2_clicked()
{
    windows_change_inf2 = new change_inf(2,cur_salesman_no);
    windows_change_inf2->show();
}
