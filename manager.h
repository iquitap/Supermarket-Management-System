#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
namespace Ui {
class manager;
}

class manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit manager(QString username,QWidget *parent = 0);
    ~manager();
    void add_new_item();
    void submit_all();
    void del_item();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_goods_add_clicked();

    void on_pushButton_manager_exit_clicked();

    void on_pushButton_goods_submit_clicked();

    void on_pushButton_card_add_clicked();

    void on_pushButton_staff_add_clicked();

    void on_pushButton_sale_add_clicked();

    void on_pushButton_supplier_add_clicked();

    void on_pushButton_card_submit_clicked();

    void on_pushButton_staff_submit_clicked();

    void on_pushButton_sale_submit_clicked();

    void on_pushButton_supplier_submit_clicked();

    void on_pushButton_goods_delete_clicked();

    void on_pushButton_card_delete_clicked();

    void on_pushButton_staff_delete_clicked();

    void on_pushButton_sale_delete_clicked();

    void on_pushButton_supplier_delete_clicked();

    void on_pushButton_supplier_return_clicked();

    void on_pushButton_turnover_return_clicked();

    void on_pushButton_sale_return_clicked();

    void on_pushButton_staff_return_clicked();

    void on_pushButton_card_return_clicked();

    void on_pushButton_goods_return_clicked();

    void on_pushButton_goods_find_clicked();

    void on_pushButton_card_find_clicked();

    void on_pushButton_staff_find_clicked();

    void on_pushButton_sale_find_2_clicked();

    void on_pushButton_sale_find_clicked();


    void on_pushButton_turnover_find_clicked();

    void on_pushButton_supplier_find_clicked();

    void on_pushButton_clicked();

private:
    QSqlTableModel *model;
    QTableView * current_table;
    Ui::manager *ui;
    QString cur_username;

    void show_table_goods();
    void show_table_staff();
    void show_table_cards();
    void show_table_sale();
    void show_table_turnover();
    void show_table_supplier();
};

#endif // MANAGER_H
