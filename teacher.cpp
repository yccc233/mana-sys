#include "teacher.h"
#include "ui_teacher.h"

Teacher::Teacher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Teacher)
{
    ui->setupUi(this);
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::on_pushButton_back_clicked()
{
    back = true;
    close();
}
