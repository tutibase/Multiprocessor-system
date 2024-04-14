#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bus = new Bus();

    for (int i = 0; i < processors_num; i++) {
        QObject::connect(bus->processors[i], &Processor::BusInvalidate,
                         bus, &Bus::BusInvalidate);

        QObject::connect(bus->processors[i], &Processor::BusShared,
                         bus, &Bus::BusShared);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_read_0_0_clicked() {
    bus->processors[0]->readLine(0);
}

void MainWindow::on_write_0_0_clicked() {
    bus->processors[0]->writeLine(0);
}


void MainWindow::on_read_0_1_clicked() {
    bus->processors[0]->readLine(1);
}

void MainWindow::on_write_0_1_clicked() {
    bus->processors[0]->writeLine(1);
}



void MainWindow::on_read_1_0_clicked() {
    bus->processors[1]->readLine(0);
}

void MainWindow::on_write_1_0_clicked() {
    bus->processors[1]->writeLine(0);
}


void MainWindow::on_read_1_1_clicked() {
    bus->processors[1]->readLine(1);
}

void MainWindow::on_write_1_1_clicked() {
    bus->processors[1]->writeLine(1);
}

