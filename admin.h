#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QInputDialog>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    QString id;
    bool back = false;
    void connectdb(QString dbname);

private slots:
    void on_pushButton_back_clicked();
    void showAccMsg();

    void on_radioButton_tea_clicked();

    void on_radioButton_stu_clicked();

    void on_pushButton_del_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_add_clicked();

private:
    Ui::Admin *ui;
    QSqlDatabase db;
    QSqlTableModel * model;
};

#endif // ADMIN_H
