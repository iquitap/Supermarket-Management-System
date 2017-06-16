#include "manager.h"
#include "ui_manager.h"
#include "mainwindow.h"
#include <QDebug>
#include "change_inf.h"
#include <QMessageBox>

change_inf * windows_change_inf;
MainWindow * windows_main2;
manager::manager(QString username,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
    show_table_goods();
    cur_username = username;
}

manager::~manager()
{
    delete ui;
}

void manager::on_pushButton_manager_exit_clicked()
{
    windows_main2 = new MainWindow();
    windows_main2->show();
    this->close();
}
void manager::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
        case 0:
            show_table_goods();
            break;
        case 1:
            show_table_cards();
            break;
        case 2:
            show_table_staff();
            break;
        case 3:
            show_table_sale();
            break;
        case 4:
            show_table_turnover();
            break;
        case 5:
            show_table_supplier();
            break;
    }
}

void manager::show_table_goods()
{
    qDebug() << "show_table_goods";
    current_table=ui->tableView_goods;
    model = new QSqlTableModel;

    model->setTable("goods_view");

    model->setHeaderData(0,Qt::Horizontal,"商品号");
    model->setHeaderData(1,Qt::Horizontal,"商品名称");
    model->setHeaderData(2,Qt::Horizontal,"库存");
    model->setHeaderData(3,Qt::Horizontal,"商品类型");
    model->setHeaderData(4,Qt::Horizontal,"单价");
    model->setHeaderData(5,Qt::Horizontal,"供应商名称");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();                //选取整个表的所有行
    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);

}

void manager::show_table_cards()
{
    qDebug() << "show_table_cards";
    current_table=ui->tableView_card;
    model = new QSqlTableModel;

    model->setTable("CARD");
    model->setFilter(QObject::tr("cno<>'00000'"));
    model->setHeaderData(0,Qt::Horizontal,"卡号");
    model->setHeaderData(1,Qt::Horizontal,"余额");
    model->setHeaderData(2,Qt::Horizontal,"累计消费");
    model->setHeaderData(3,Qt::Horizontal,"办卡时间");
    model->setHeaderData(4,Qt::Horizontal,"过期时间");
    model->setHeaderData(5,Qt::Horizontal,"会员姓名");
    model->setHeaderData(6,Qt::Horizontal,"会员电话");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setSort(0,Qt::AscendingOrder);
    model->select();                //选取整个表的所有行
    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void manager::show_table_staff()
{
    qDebug() << "show_table_staff";
    current_table=ui->tableView_staff;
    model = new QSqlTableModel;

    model->setTable("staff");

    model->setHeaderData(0,Qt::Horizontal,"工号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"电话");
    model->setHeaderData(3,Qt::Horizontal,"部门");
    model->setHeaderData(4,Qt::Horizontal,"登录名");
    model->setHeaderData(5,Qt::Horizontal,"密码");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();                //选取整个表的所有行
    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void manager::show_table_sale()
{
    qDebug() << "show_table_order";
    current_table=ui->tableView_sale;
    model = new QSqlTableModel;

    model->setTable("sale_view");

    model->setHeaderData(0,Qt::Horizontal,"订单号");
    model->setHeaderData(1,Qt::Horizontal,"会员卡号");
    model->setHeaderData(2,Qt::Horizontal,"商品号");
    model->setHeaderData(3,Qt::Horizontal,"时间");
    model->setHeaderData(4,Qt::Horizontal,"数目");
    model->setHeaderData(5,Qt::Horizontal,"总价");
    model->setHeaderData(6,Qt::Horizontal,"营业员工号");
    model->setHeaderData(7,Qt::Horizontal,"营业员姓名");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();

    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void manager::show_table_turnover()
{
    qDebug() << "show_table_order";
    current_table=ui->tableView_turnover;
    model = new QSqlTableModel;

    model->setTable("turnover");

    model->setHeaderData(0,Qt::Horizontal,"日期");
    model->setHeaderData(1,Qt::Horizontal,"营业额");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

void manager::show_table_supplier()
{
    qDebug() << "show_table_supplier";
    current_table=ui->tableView_supplier;
    model = new QSqlTableModel;

    model->setTable("SUPPLIER");

    model->setHeaderData(0,Qt::Horizontal,"供应商号");
    model->setHeaderData(1,Qt::Horizontal,"供应商名称");
    model->setHeaderData(2,Qt::Horizontal,"联系方式");
    model->setHeaderData(3,Qt::Horizontal,"地址");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    current_table->setModel(model);
    current_table->horizontalHeader()->setStretchLastSection(true);
}

//新增
void manager::add_new_item()
{
    if(model)
    {
        model->insertRow(model->rowCount());
    }
}

void manager::on_pushButton_goods_add_clicked()
{
    add_new_item();
}

void manager::on_pushButton_card_add_clicked()
{
     add_new_item();
}

void manager::on_pushButton_staff_add_clicked()
{
    add_new_item();
}

void manager::on_pushButton_sale_add_clicked()
{
     add_new_item();
}

void manager::on_pushButton_supplier_add_clicked()
{
    add_new_item();
}

//修改
void manager::submit_all()
{
    if(model)
    {
        model->database().transaction(); //开始事务操作
        if(model->submitAll())//提交修改到数据库中
        {
            //QMessageBox::about(NULL,"ok","修改成功");
            model->database().commit(); //提交成功，事务操作将保存数据到数据库中
        }
        else
        {
            qDebug() << "修改失败";
            model->database().rollback(); //回滚
            QMessageBox::warning(this,"提示","提交失败","确定");
        }
    }
}

void manager::on_pushButton_goods_submit_clicked()
{
    submit_all();
    show_table_goods();
}

void manager::on_pushButton_card_submit_clicked()
{
    submit_all();
    show_table_cards();
}

void manager::on_pushButton_staff_submit_clicked()
{
    submit_all();
    show_table_staff();
}

void manager::on_pushButton_sale_submit_clicked()
{
    submit_all();
    show_table_sale();
}

void manager::on_pushButton_supplier_submit_clicked()
{
    submit_all();
    show_table_supplier();
}

//删除
void manager::del_item()
{
    if(model)
    {
        int curRow=current_table->currentIndex().row();
        //获取选中的行
        if(curRow!=-1)
        {
            int ok = QMessageBox::warning(this,"提示","是否删除选中行",QMessageBox::Yes,QMessageBox::No);
            if(ok == QMessageBox::Yes)
            {
                model->removeRow(curRow);
                model->submitAll();
            }
        }
    }
}

void manager::on_pushButton_goods_delete_clicked()
{
    del_item();
    show_table_goods();
}

void manager::on_pushButton_card_delete_clicked()
{
    del_item();
    show_table_cards();
}

void manager::on_pushButton_staff_delete_clicked()
{
    del_item();
    show_table_staff();
}

void manager::on_pushButton_sale_delete_clicked()
{
    del_item();
    show_table_sale();
}

void manager::on_pushButton_supplier_delete_clicked()
{
    del_item();
    show_table_supplier();
}

//返回全表
void manager::on_pushButton_supplier_return_clicked()
{
    show_table_supplier();
}

void manager::on_pushButton_turnover_return_clicked()
{
    show_table_turnover();
}

void manager::on_pushButton_sale_return_clicked()
{
    show_table_sale();
}

void manager::on_pushButton_staff_return_clicked()
{
    show_table_staff();
}

void manager::on_pushButton_card_return_clicked()
{
    show_table_cards();
}

void manager::on_pushButton_goods_return_clicked()
{
    show_table_goods();
}

//查找
void manager::on_pushButton_goods_find_clicked()
{
    QString str;
    str=ui->lineEdit_good->text();
    model->setFilter(QObject::tr("gno=\'%1\' or gname=\'%1\' or gstock=\'%1\' or gtype=\'%1\' or  gprice=\'%1\' or suname=\'%1\'").arg(str));
}

void manager::on_pushButton_card_find_clicked()
{
    QString str;
    str=ui->lineEdit_card->text();
    model->setFilter(QObject::tr("cno=\'%1\' or cname=\'%1\' or cphone=\'%1\'").arg(str));
}

void manager::on_pushButton_staff_find_clicked()
{
    QString str;
    str=ui->lineEdit_staff->text();
    model->setFilter(QObject::tr("sno=\'%1\' or sname=\'%1\' or sphone=\'%1\' or spart=\'%1\' or saccount=\'%1\' or spsw=\'%1\'").arg(str));
}

void manager::on_pushButton_sale_find_clicked()
{
    QString str;
    str=ui->lineEdit_sale->text();
    model->setFilter(QObject::tr("sano=\'%1\' or cno=\'%1\' or gno=\'%1\' or satype=\'%1\' or sno=\'%1\'").arg(str));
}

void manager::on_pushButton_sale_find_2_clicked()
{
    QDate date = ui->dateEdit_sale->date();
    model->setFilter(QObject::tr("convert(varchar(50),odate,120) like \'%1%\'").arg(date.toString("yyyy-MM-dd")));
}


void manager::on_pushButton_turnover_find_clicked()
{
    QDate date = ui->dateEdit_turnover->date();
    model->setFilter(QObject::tr("convert(varchar(50),odate,120) like \'%1%\'").arg(date.toString("yyyy-MM-dd")));
}

void manager::on_pushButton_supplier_find_clicked()
{
    QString str;
    str=ui->lineEdit_supplier->text();
    model->setFilter(QObject::tr("suno=\'%1\' or suname=\'%1\' or suphone=\'%1\' or suaddr=\'%1\'").arg(str));
}

void manager::on_pushButton_clicked()
{
    windows_change_inf = new change_inf(1,cur_username);
    windows_change_inf->show();
}
