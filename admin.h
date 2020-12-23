#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    int id;
    bool back = false;

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
