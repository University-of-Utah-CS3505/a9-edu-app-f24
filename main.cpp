#include "educationalapp.h"

#include <QApplication>
#include <character.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    EducationalApp w(m);
    w.show();
    return a.exec();
}
