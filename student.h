#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Student;
}

class Student : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr, QString id = NULL);
    ~Student();
    QString id;
    bool back = false;
    void connectdb(QString dbname);

private slots:
    void on_radioButton_info_clicked();

    void on_radioButton_score_clicked();

    void on_pushButton_back_clicked();

    void setHeadData(QStringList heads);

private:
    Ui::Student *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // STUDENT_H
