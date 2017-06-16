#ifndef GOODSMAN_H
#define GOODSMAN_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class goodsman;
}

class goodsman : public QMainWindow
{
    Q_OBJECT

public:
    explicit goodsman(QString sno,QWidget *parent = 0);
    ~goodsman();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_import_clicked();

    void on_pushButton_stock_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::goodsman *ui;
    QString cur_goodsman_no;
    QSqlTableModel *model;
};

#endif // GOODSMAN_H
