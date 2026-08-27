#include "mainwindow.h"
#include <QApplication>
#include <clocale>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
