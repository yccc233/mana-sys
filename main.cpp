#include "login.h"
#include "student.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    a.exec();
    if(!w.NextUI){
        return 0;
    }
    Student s;
    switch (w.NextUI) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        s.id = w.id;
        s.show();
        a.exec();
        break;
    default:
        break;
    }
    return 0;
}

