#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDebug>
#include "saleman.h"
#include "manager.h"
#include "goodsman.h"
//#include <mysql.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_exit_clicked();

private:
    QSqlTableModel *model;
    QTableView * current_table;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
