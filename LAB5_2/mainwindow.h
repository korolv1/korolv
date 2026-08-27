#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "classes.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadData();
    void onRowDoubleClicked(int row, int column);

private:
    QTableWidget *tableWidget;
    QPushButton *btnLoad;
    std::vector<R*> entries;

    void updateTable();
    void clearData();
};

#endif
