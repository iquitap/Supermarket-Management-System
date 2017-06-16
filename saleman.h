#ifndef SALEMAN_H
#define SALEMAN_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class saleman;
}

class saleman : public QMainWindow
{
    Q_OBJECT

public:
    explicit saleman(QString sno,QWidget *parent = 0);
    ~saleman();
    QString ToStr(int number, int size)
    {
        return QString("%1").arg(number, size, 10, QChar('0'));
    }
    void sale_initial();
    void card_initial();
    bool check_account(QString cno);
    QString get_new_sano();

private slots:

    void on_pushButton_cashier_exit_clicked();

    void on_pushButton_cashier_exit_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_cashier_settle_clicked();

    void on_pushButton_cashier_add_clicked();

    void on_pushButton_cashier_delete_clicked();

    void on_pushButton_cashier_settle_2_clicked();

private:
    Ui::saleman *ui;
    QSqlTableModel *model;
    QDateTime current_date_time;
    QString cur_salesman_no;
    QString cur_card_no;
    bool cashier_satype;
    double cashier_total_money;
    int cashier_total_amount;
    double all_1,all_2,all_3;
};


#endif // SALEMAN_H
