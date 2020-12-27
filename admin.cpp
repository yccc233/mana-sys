#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    connectdb("SYS_MAN.db");

    model = new QSqlTableModel(this);
    ui->tableView->setModel(model);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::connectdb(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("DataBase Error"),db.lastError().text());
    }
}


void Admin::showAccMsg()
{

}

void Admin::on_pushButton_back_clicked()
{
    back = true;
    close();
}

void Admin::on_radioButton_tea_clicked()
{
    model->setTable("teach_acc");
    model->select();
}

void Admin::on_radioButton_stu_clicked()
{
    model->setTable("stu_acc");
    model->select();
}
