#ifndef CHANGE_INF_H
#define CHANGE_INF_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class change_inf;
}

class change_inf : public QMainWindow
{
    Q_OBJECT

public:
    explicit change_inf(int i,QString no,QWidget *parent = 0);
    ~change_inf();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::change_inf *ui;
    QSqlTableModel *model;
    int option;
    QString cur_no;
};

#endif // CHANGE_INF_H

