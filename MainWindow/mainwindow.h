#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Bus/bus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_read_0_clicked();
    void on_write_0_clicked();


    void on_read_1_clicked();

    void on_write_1_clicked();

    void on_read_2_clicked();

    void on_write_2_clicked();

    void on_read_3_clicked();

    void on_write_3_clicked();

private:
    Ui::MainWindow *ui;
    Bus *bus;

};
#endif // MAINWINDOW_H
