#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    connectdb("SYS_MAN.db");
    model = new QSqlTableModel(this,db);

    ui->tableView->setModel(model);
}

Student::~Student()
{
    delete ui;
}

void Student::connectdb(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("DataBase Error"),db.lastError().text());
    }
}

void Student::on_radioButton_info_clicked()
{
    model->setTable("stu_info");
    model->setFilter(QString("stu_id=%1").arg(id));
    model->select();
}

void Student::on_radioButton_score_clicked()
{
    model->setTable("stu_score");
    model->setFilter(QString("stu_id=%1").arg(id));
    model->select();
}

void Student::on_pushButton_back_clicked()
{
    back = true;
    close();
}
