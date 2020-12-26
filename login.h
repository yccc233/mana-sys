#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    int NextUI = 0;//0 退出， 1、2、3分别对应管理员、教师、学生
    QString id;
    void connectdb(QString dbname);

private slots:
    void on_pushButton_login_clicked();

    void on_radioButton_admin_clicked();

    void on_radioButton_tech_clicked();

    void on_radioButton_stu_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase db;
    QMap<QString,QString> acc_pw;
};
#endif // LOGIN_H
