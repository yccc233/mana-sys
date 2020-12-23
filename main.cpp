#include "login.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication e(argc, argv);
    while(true){
        Login l;
        l.show();
        e.exec();
        if(!l.NextUI){
            return 0;
        }
        Student s;
        Teacher t;
        Admin a;
        switch (l.NextUI) {
        case 1:
            a.id = l.id;
            a.show();
            e.exec();
            if(!a.back) return 0;
            break;
        case 2:
            t.id = l.id;
            t.show();
            e.exec();
            if(!t.back) return 0;
            break;
        case 3:
            s.id = l.id;
            s.show();
            e.exec();
            if(!s.back) return 0;
            break;
        default:
            return 0;
        }
    }
    return 0;
}

