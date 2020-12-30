#include "login.h"
#include "ui_login.h"
#include "qdebug.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //界面优化
    setWindowFlag(Qt::FramelessWindowHint);
    ui->lineEdit_acc->setPlaceholderText(" //输入账号");
    ui->lineEdit_pw->setPlaceholderText(" //输入密码");
    QPixmap labelmap(QString("%1/src/img/login.png").arg(QCoreApplication::applicationDirPath()));
    ui->label_pic->setPixmap(labelmap);
    ui->label_pic->setScaledContents(true);
    ui->label_pic->adjustSize();

    connectdb(QString("%1/SYS_MAN.db").arg(QCoreApplication::applicationDirPath()));
    ui->radioButton_stu->setChecked(true);
    emit ui->radioButton_stu->clicked(true);

    //申明下拉框
    model = new QStandardItemModel(0,1,this);
    ui->lineEdit_acc->setCompleter(new QCompleter(model,this));

    //图标
    QAction *act_acc = new QAction;
    act_acc->setIcon(QIcon(QString("%1/src/img/acc.png").arg(QCoreApplication::applicationDirPath())));
    ui->lineEdit_acc->addAction(act_acc,QLineEdit::TrailingPosition);
    QAction *act_pw = new QAction;
    act_pw->setIcon(QIcon(QString("%1/src/img/pw.png").arg(QCoreApplication::applicationDirPath())));
    ui->lineEdit_pw->addAction(act_pw,QLineEdit::TrailingPosition);
}

Login::~Login()
{
    delete ui;
}

void Login::connectdb(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("DataBase Error"),db.lastError().text());
    }
}

void Login::on_radioButton_admin_clicked()
{
    acc_pw.clear();
    linelist.clear();
    acc_pw.insert("root","1111");
    qDebug() << acc_pw;
}

void Login::on_radioButton_tech_clicked()
{
    acc_pw.clear();
    linelist.clear();
    QSqlQuery query(db);
    if(!query.exec("select * from teach_acc"))
        QMessageBox::warning(this,"错误","数据检索失败!\n"+query.lastError().text());
    while(query.next())
    {
        acc_pw.insert(query.value(1).toString(),query.value(2).toString());
        linelist.append(query.value(1).toString());
    }
    qDebug() << acc_pw;
}

void Login::on_radioButton_stu_clicked()
{
    acc_pw.clear();
    linelist.clear();
    QSqlQuery query(db);
    if(!query.exec("select * from stu_acc"))
         QMessageBox::warning(this,"错误","数据检索失败!\n"+query.lastError().text());
    while(query.next())
    {
        acc_pw.insert(query.value(1).toString(),query.value(2).toString());
        linelist.append(query.value(1).toString());
    }
    qDebug() << acc_pw;
}

void Login::on_pushButton_login_clicked()
{
    if(ui->radioButton_admin->isChecked())
    {
        NextUI = 1;
    }
    else if(ui->radioButton_tech->isChecked())
    {
        NextUI = 2;
    }
    else
    {
        NextUI = 3;
    }
    QString account = ui->lineEdit_acc->text();
    QString password = ui->lineEdit_pw->text();

    if(acc_pw.contains(account) && acc_pw.find(account).value() == password)
    {
        id = account;
        close();
    }
    else
    {
        QMessageBox::warning(this,"err","账号或密码错误！");
        ui->lineEdit_pw->clear();
    }
}

void Login::on_pushButton_quit_clicked()
{
    NextUI = 0;
    close();
}

void Login::on_lineEdit_acc_textChanged(const QString &arg1)
{
    model->removeRows(0,model->rowCount());
    for(int i=0;i<linelist.size();i++)
    {
        if(linelist[i].contains(arg1))
        {
            model->insertRow(0);
            model->setData(model->index(0,0),linelist[i]);
        }
    }
}
