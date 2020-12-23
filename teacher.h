#ifndef TEACHER_H
#define TEACHER_H

#include <QMainWindow>

namespace Ui {
class Teacher;
}

class Teacher : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teacher(QWidget *parent = nullptr);
    ~Teacher();
    int id;
    bool back = false;

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::Teacher *ui;
};

#endif // TEACHER_H
