#include <QApplication>
#include "registrationform.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RegistrationForm w;
    w.show();
    return a.exec();
}
