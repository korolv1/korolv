#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(0, 2, this);
    tableWidget->setHorizontalHeaderLabels({"ФИО / Имя", "Дата рождения"});
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    btnLoad = new QPushButton("Загрузить", this);
    btnLoad->setStyleSheet("font-size: 14px; font-weight: bold; padding: 10px; background-color: lightblue;");

    layout->addWidget(tableWidget);
    layout->addWidget(btnLoad);
    setCentralWidget(centralWidget);
    resize(500, 400);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::onRowDoubleClicked);
}

MainWindow::~MainWindow() {
    clearData();
}

void MainWindow::clearData() {
    for (R* ptr : entries) {
        delete ptr;
    }
    entries.clear();
}

void MainWindow::loadData() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Текстовые файлы (*.txt);;CSV файлы (*.csv);;Все файлы (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    clearData();
    QTextStream in(&file);
    int lineNum = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineNum++;
        if (line.isEmpty()) continue;

        QStringList parts = line.split(",");
        for (QString& p : parts) p = p.trimmed();

        try {
            if (parts.size() < 7) throw std::invalid_argument("Недостаточно данных.");

            int code = parts[0].toInt();

            if (code == 1) {
                int d = parts[4].toInt();
                int m = parts[5].toInt();
                int y = parts[6].toInt();
                if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) throw std::invalid_argument("Неверная дата.");
                entries.push_back(new RuP(parts[1], parts[2], parts[3], {d, m, y}));
            }
            else if (code == 2) {
                int m = parts[4].toInt();
                int d = parts[5].toInt();
                int y = parts[6].toInt();
                if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) throw std::invalid_argument("Неверная дата.");
                entries.push_back(new AmP(parts[1], parts[2], parts[3], {d, m, y}));
            }
            else {
                throw std::invalid_argument("Неизвестный код класса.");
            }
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Ошибка чтения", QString("Ошибка в строке %1: %2\nСтрока пропущена.").arg(lineNum).arg(e.what()));
        }
    }

    file.close();
    updateTable();
}

void MainWindow::updateTable() {
    tableWidget->setRowCount(0);
    for (size_t i = 0; i < entries.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(entries[i]->getTableNames()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(entries[i]->getTableDate()));
    }
}

void MainWindow::onRowDoubleClicked(int row, int column) {
    if (row < 0 || row >= static_cast<int>(entries.size())) return;

    R* selectedPerson = entries[row];
    QDialog* passDialog = selectedPerson->Craft(this);

    if (passDialog->exec() == QDialog::Accepted) {
        delete selectedPerson;
        entries.erase(entries.begin() + row);
        updateTable();
    }

    delete passDialog;
}
