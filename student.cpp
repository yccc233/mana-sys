#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent, QString id) :
    QMainWindow(parent),id(id),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    connectdb(QString("%1/SYS_MAN.db").arg(QCoreApplication::applicationDirPath()));
    model = new QSqlTableModel(this,db);

    ui->tableView->setModel(model);

    setWindowTitle("学生查询系统");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void Student::setHeadData(QStringList heads)
{
    for(int i=0;i<heads.size();i++)
        model->setHeaderData(i,Qt::Horizontal,heads[i]);
}

void Student::on_radioButton_info_clicked()
{
    QStringList heads;
    heads << "id" << "学号" << "姓名" << "性别";


    model->setTable("stu_info");
    model->setFilter(QString("stu_id=%1").arg(id));
    model->select();

    setHeadData(heads);
}

void Student::on_radioButton_score_clicked()
{
    QStringList heads;
    heads << "id" << "学号" << "科目" << "分数" << "科目" << "分数" << "科目" << "分数";
    QVector<int> sizes;
    sizes << 80 << 80 << 40 << 40 << 40 << 40 << 40 << 40 << 40 << 40;

    model->setTable("stu_score");
    model->setFilter(QString("stu_id=%1").arg(id));
    model->select();

    setHeadData(heads);
}

void Student::on_pushButton_back_clicked()
{
    back = true;
    close();
}
