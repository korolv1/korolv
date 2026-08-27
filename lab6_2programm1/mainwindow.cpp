#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnLoadTxt_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть TXT", "", "*.txt");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Utf8);
        ui->editName->setText(in.readLine().trimmed());
        ui->editDesc->setText(in.readLine().trimmed());
        ui->editColor->setText(in.readLine().trimmed());
        ui->editInk->setText(in.readLine().trimmed());
        file.close();
    }
}

void MainWindow::on_btnOk_clicked() {
    QJsonObject obj;
    obj["name"] = ui->editName->text().trimmed();
    obj["desc"] = ui->editDesc->text().trimmed();
    obj["color"] = ui->editColor->text().trimmed();

    QString inkStr = ui->editInk->text().trimmed();
    bool inkOk;
    double ink = inkStr.toDouble(&inkOk);

    if (inkOk && ink >= 0) {
        obj["inkLevel"] = ink;
    } else {
        obj["inkLevel"] = "";
    }

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QFile file(desktopPath + "/marker.json");

    QJsonArray array;
    if (file.open(QIODevice::ReadOnly)) {
        array = QJsonDocument::fromJson(file.readAll()).array();
        file.close();
    }

    array.append(obj);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson());
        file.close();
        QMessageBox::information(this, "Успех", "Объект добавлен в marker.json на Рабочем столе");

        ui->editName->clear(); ui->editDesc->clear();
        ui->editColor->clear(); ui->editInk->clear();
    }
}
