#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <vector>
#include <algorithm>

class Marker {
public:
    QString name;
    QString desc;
    QString color;
    QString inkLevel;

    Marker(QString n, QString d, QString c, QString i)
        : name(n), desc(d), color(c), inkLevel(i) {}
};

bool isNumericFieldValid(const QString &str) {
    if (str.trimmed().isEmpty()) return false;
    if (str.trimmed().startsWith("0") && str.trimmed().length() > 1
        && !str.trimmed().startsWith("0.")) return false;
    bool ok;
    double val = str.trimmed().toDouble(&ok);
    if (!ok || val < 0) return false;
    return true;
}

QStringList getBrokenFields(const Marker &m) {
    QStringList broken;
    if (m.name.trimmed().isEmpty())          broken << "name";
    if (m.desc.trimmed().isEmpty())          broken << "desc";
    if (m.color.trimmed().isEmpty())         broken << "color";
    if (!isNumericFieldValid(m.inkLevel))    broken << "inkLevel";
    return broken;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableValid->setColumnCount(4);
    ui->tableValid->setHorizontalHeaderLabels({"Название", "Описание", "Цвет", "Уровень чернил"});
    ui->tableValid->horizontalHeader()->setStretchLastSection(true);

    ui->tableBroken->setColumnCount(4);
    ui->tableBroken->setHorizontalHeaderLabels({"Название", "Описание", "Цвет", "Уровень чернил"});
    ui->tableBroken->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnLoad_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть JSON", "", "*.json");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }
    QString rawText = file.readAll();
    file.close();

    QRegularExpression re(":\\s*(0\\d+)([,}\\s])");
    rawText.replace(re, ": \"\\1\"\\2");

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawText.toUtf8(), &parseError);

    if (!doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", QString("Не удалось прочитать файл: %1").arg(parseError.errorString()));
        return;
    }

    const QJsonArray all = doc.array();
    std::vector<Marker> validList, brokenList;

    for (const QJsonValue &val : all) {
        if (!val.isObject()) continue;
        QJsonObject obj = val.toObject();

        auto fieldStr = [&](const QString &key) -> QString {
            QJsonValue v = obj[key];
            if (v.isString()) return v.toString();
            if (v.isDouble()) return QString::number(v.toDouble(), 'g', 10);
            return "";
        };

        Marker markerObj(
            fieldStr("name"),
            fieldStr("desc"),
            fieldStr("color"),
            fieldStr("inkLevel")
            );

        if (getBrokenFields(markerObj).isEmpty())
            validList.push_back(markerObj);
        else
            brokenList.push_back(markerObj);
    }

    std::sort(validList.begin(), validList.end(), [](const Marker &a, const Marker &b) {
        return a.name < b.name;
    });

    fillTables(validList, brokenList);


    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QFile brokenFile(desktopPath + "/marker_broken.json");
    if (brokenFile.open(QIODevice::WriteOnly)) {
        QJsonArray brokenArr;
        for (const Marker &m : brokenList) {
            QJsonObject o;
            o["name"]     = m.name;
            o["desc"]     = m.desc;
            o["color"]    = m.color;
            o["inkLevel"] = m.inkLevel;
            brokenArr.append(o);
        }
        brokenFile.write(QJsonDocument(brokenArr).toJson());
        brokenFile.close();
    }

    QMessageBox::information(this, "Готово",
                             QString("Корректных: %1\nБитых: %2\nБитые сохранены в marker_broken.json")
                                 .arg(validList.size()).arg(brokenList.size()));
}

void MainWindow::fillTables(const std::vector<Marker> &validList, const std::vector<Marker> &brokenList) {
    ui->tableValid->setRowCount(0);
    ui->tableBroken->setRowCount(0);

    for (const Marker &m : validList) {
        int row = ui->tableValid->rowCount();
        ui->tableValid->insertRow(row);
        ui->tableValid->setItem(row, 0, new QTableWidgetItem(m.name));
        ui->tableValid->setItem(row, 1, new QTableWidgetItem(m.desc));
        ui->tableValid->setItem(row, 2, new QTableWidgetItem(m.color));
        ui->tableValid->setItem(row, 3, new QTableWidgetItem(m.inkLevel));
    }

    for (const Marker &m : brokenList) {
        QStringList broken = getBrokenFields(m);
        int row = ui->tableBroken->rowCount();
        ui->tableBroken->insertRow(row);

        auto makeItem = [&](const QString &val, const QString &key) {
            QTableWidgetItem *item = new QTableWidgetItem(val);
            if (broken.contains(key))
                item->setBackground(QColor(255, 180, 180));
            return item;
        };

        ui->tableBroken->setItem(row, 0, makeItem(m.name,     "name"));
        ui->tableBroken->setItem(row, 1, makeItem(m.desc,     "desc"));
        ui->tableBroken->setItem(row, 2, makeItem(m.color,    "color"));
        ui->tableBroken->setItem(row, 3, makeItem(m.inkLevel, "inkLevel"));
    }
}
