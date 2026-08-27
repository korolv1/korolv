#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QJsonArray>
#include <vector>

class Marker;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btnLoad_clicked();
private:
    Ui::MainWindow *ui;
    void fillTables(const std::vector<Marker> &validList, const std::vector<Marker> &brokenList);
};
#endif
