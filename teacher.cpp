#include "teacher.h"
#include "ui_teacher.h"

Teacher::Teacher(QWidget *parent, QString id) :
    QMainWindow(parent),id(id),
    ui(new Ui::Teacher)
{
    ui->setupUi(this);
    setWindowTitle("教师管理系统");
    connectdb(QString("%1/SYS_MAN.db").arg(QCoreApplication::applicationDirPath()));

    //获取教师教学courseid
    query = new QSqlQuery(db);

    query->exec(QString("select * from teach_info where teach_id='%1';").arg(id));
    query->next();

    QString course = query->record().value("teach_course").toString();
    if(course == "语文")
        courseid = 1;
    else if(course == "数学")
        courseid = 2;
    else
        courseid = 3;

    model = new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
    showStuScore();

    ui->show_info->setText(QString("\t教师id:%1\t姓名:%2\n\n\t性别:%3\t电话号码:%4\t授课:%5")
                           .arg(query->record().value("teach_id").toString())
                           .arg(query->record().value("teach_name").toString())
                           .arg(query->record().value("teach_gender").toString())
                           .arg(query->record().value("teach_tele").toString())
                           .arg(query->record().value("teach_course").toString())
                           );
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //搜索栏图标
    QAction *act = new QAction;
    act->setIcon(QIcon(QString("%1/src/img/search.png").arg(QCoreApplication::applicationDirPath())));
    ui->lineEdit->addAction(act,QLineEdit::TrailingPosition);

    //申明下拉框
    mod = new QStandardItemModel(0,1,this);
    ui->lineEdit->setCompleter(new QCompleter(mod,this));

    query->exec("select stu_id from stu_score;");
    while(query->next())
        linelist.append(query->value(0).toString());

    connect(ui->tableView->horizontalHeader(),&QHeaderView::sectionClicked,this,&Teacher::setSortWay);
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::showStuScore()
{
    model->setTable("stu_score");
    for(int i=3;i>=1;i--)
    {
        if(courseid == i) continue;
        model->removeColumns(2*i,2);
    }
    model->select();
    setHeadData();
}

void Teacher::setHeadData()
{
    QStringList heads;
    QVector<int> sizes;
    heads << "id" << "学生学号" << "科目" << "成绩";
    sizes << 80 << 80 << 40 << 40;
    for(int i=0;i<heads.size();i++)
        model->setHeaderData(i,Qt::Horizontal,heads[i]);
    for(int i=0;i<sizes.size();i++)
        ui->tableView->setColumnWidth(i,sizes[i]);
}

void Teacher::connectdb(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("DataBase Error"),db.lastError().text());
    }
}

void Teacher::on_pushButton_back_clicked()
{
    back = true;
    close();
}

void Teacher::on_pushButton_info_clicked()
{

}

void Teacher::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() < 3)
        return;
    bool isOk;
    QString ipAdress = QInputDialog::getText(NULL,"修改","输入修改后的值",QLineEdit::Normal,
                                             model->index(index.row(),index.column()).data().toString(),&isOk);
    if(!isOk)
        return;
    model->setData(index,ipAdress);
    model->submit();
}

void Teacher::on_pushButton_sea_clicked()
{    
    if(ui->lineEdit->text().isEmpty())
        return;
    model->setFilter(QString("stu_id='%1'").arg(ui->lineEdit->text()));
    model->select();
}

void Teacher::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        showStuScore();
    }
    else
    {
        mod->removeRows(0,mod->rowCount());
        for(int i=0;i<linelist.size();i++)
        {
            if(linelist[i].contains(arg1))
            {
                mod->insertRow(0);
                mod->setData(mod->index(0,0),linelist[i]);
            }
        }
    }
}

void Teacher::setSortWay()
{
    static bool Asc = false;
    if(Asc)
    {
        model->setSort(ui->tableView->currentIndex().column(),Qt::AscendingOrder);
    }
    else
    {
        model->setSort(ui->tableView->currentIndex().column(),Qt::DescendingOrder);
    }
    Asc = !Asc;
    model->select();
}
