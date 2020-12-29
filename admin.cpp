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

    setWindowTitle("管理员系统");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void Admin::setHeadData()
{
    QStringList heads;
    QVector<int> sizes;
    if(ui->radioButton_stu->isChecked())
    {
        heads << "id" << "学号" << "学生姓名" << "性别";
        sizes << 80 << 80 << 80 << 40;
    }
    else if(ui->radioButton_tea->isChecked())
    {
        heads << "id" << "教师号" << "姓名" << "性别" << "电话" << "授课";
        sizes << 80 << 80 << 80 << 40 << 100 << 50;
    }
    else
    {
        heads << "id" << "账号" << "密码";
        sizes << 80 << 80 << 80;
    }
    for(int i=0;i<heads.size();i++)
        model->setHeaderData(i,Qt::Horizontal,heads[i]);
    for(int i=0;i<sizes.size();i++)
        ui->tableView->setColumnWidth(i,sizes[i]);
}

void Admin::on_pushButton_back_clicked()
{
    back = true;
    close();
}

void Admin::on_radioButton_tea_acc_clicked()     //*****开始修改
{
    model->setTable("teach_acc");
    model->select();
    setHeadData();
}

void Admin::on_radioButton_stu_acc_clicked()
{
    model->setTable("stu_acc");
    model->select();
    setHeadData();
}                                                //****结束

void Admin::on_radioButton_tea_clicked()
{
    model->setTable("teach_info");
    model->select();
    setHeadData();
}

void Admin::on_radioButton_stu_clicked()
{
    model->setTable("stu_info");
    model->select();
    setHeadData();
}

void Admin::on_pushButton_del_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row < 0)
        return;
    if(QMessageBox::Ok == QMessageBox::question(this,"删除",QString("确定删除第%1行吗？").arg(row+1),QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok))
    {
        model->removeRow(ui->tableView->currentIndex().row());
        model->submit();
        model->select();
        setHeadData();
    }
}


void Admin::on_tableView_doubleClicked(const QModelIndex &index)
{
    bool isOk;
    QString ipAdress = QInputDialog::getText(NULL,"修改","输入修改后的值",QLineEdit::Normal,model->index(index.row(),index.column()).data().toString(),&isOk);
    if(!isOk)
        return;
    model->setData(index,ipAdress);
    model->submit();
}

void Admin::on_pushButton_add_clicked()
{
    if(model->columnCount() <= 0)
        return;
    QStringList ins;
    QStringList head;
    if(ui->radioButton_stu->isChecked())   //**********************修改
        head << "id" << "学号" << "姓名" << "性别";
    else if(ui->radioButton_tea->isChecked())
        head << "id" << "教师号" << "姓名" << "性别" << "电话号码" << "授课名称";
    else if(ui->radioButton_tea_acc->isChecked())
        head << "id" << "账户" << "密码";
    else
        head << "id" << "账户" << "密码";  //************************结束
    for(int i=0;i<head.size();i++)
    {
        bool isOk;
        ins << QInputDialog::getText(this,"录入",head[i],QLineEdit::Normal,"",&isOk);
        if(!isOk)
            return;
    }
    int row = model->rowCount();
    model->insertRow(row);
    for(int i=0;i<head.size();i++)
    {
        model->setData(model->index(row,i),ins[i]);
    }
    model->submitAll();
    model->select();
}


