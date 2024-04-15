#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bus = new Bus();

    ui->log->insertPlainText("MESIF protocol with \"least frequently used\" replacement policy:\n");

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


void MainWindow::on_read_0_clicked() {
    int address = ui->comboBox_0->currentIndex();
    bus->processors[0]->readLine(address);
}

void MainWindow::on_write_0_clicked() {
    int address = ui->comboBox_0->currentIndex();
    bus->processors[0]->writeLine(address);
}




void MainWindow::on_read_1_clicked() {
    int address = ui->comboBox_1->currentIndex();
    bus->processors[1]->readLine(address);
}

void MainWindow::on_write_1_clicked() {
    int address = ui->comboBox_1->currentIndex();
    bus->processors[1]->writeLine(address);
}



void MainWindow::on_read_2_clicked() {
    int address = ui->comboBox_2->currentIndex();
    bus->processors[2]->readLine(address);
}

void MainWindow::on_write_2_clicked() {
    int address = ui->comboBox_2->currentIndex();
    bus->processors[2]->writeLine(address);
}



void MainWindow::on_read_3_clicked() {
    int address = ui->comboBox_3->currentIndex();
    bus->processors[3]->readLine(address);
}

void MainWindow::on_write_3_clicked() {
    int address = ui->comboBox_3->currentIndex();
    bus->processors[3]->writeLine(address);
}

