#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <bitset>
#include "../Bus/bus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using CacheLabels = QVector<QLabel*>;
enum Clicking {
    Read,
    Write
};
using Caller = QPair<int, Clicking>;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateLog(QString msg);

private slots:
    void on_read_0_clicked();
    void on_write_0_clicked();


    void on_read_1_clicked();

    void on_write_1_clicked();

    void on_read_2_clicked();

    void on_write_2_clicked();

    void on_read_3_clicked();

    void on_write_3_clicked();

    void updateCache();

    void updateMemory();

    void on_sim_call_box_stateChanged(int state);

    void on_confirm_button_clicked();

private:
    Ui::MainWindow *ui;
    Bus *bus;
    QVector<CacheLabels> CPULabels;
    QVector<QLabel*> memory_labels;
    QVector<QPair<Caller, int>> callings;

};
#endif // MAINWINDOW_H
