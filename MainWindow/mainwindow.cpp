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

        /*QObject::connect(bus->processors[i], &Processor::BusShared,
                         bus, &Bus::BusShared);*/

        QObject::connect(bus->processors[i], &Processor::BusRead,
                         bus, &Bus::BusRead);
        QObject::connect(bus->processors[i], &Processor::BusRWITM,
                         bus, &Bus::BusRWITM);
        QObject::connect(bus->processors[i], &Processor::updateLog,
                         bus, &Bus::updateLogSlot);
        QObject::connect(bus->processors[i], &Processor::updateCacheView,
                         this, &MainWindow::updateCache);
    }
    QObject::connect(bus, &Bus::updateLog,
                     this, &MainWindow::updateLog);
    QObject::connect(bus, &Bus::updateCacheView, this, &MainWindow::updateCache);
    QObject::connect(bus, &Bus::updateMemoryView, this, &MainWindow::updateMemory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLog(QString msg) {
    ui->log->insertPlainText('\n' + msg);
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

void MainWindow::updateCache() {
    auto cache = bus->processors[0]->getCache()[0];
    ui->cache_0_0->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[0]->getCache()[1];
    ui->cache_0_1->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[0]->getCache()[2];
    ui->cache_0_2->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[0]->getCache()[3];
    ui->cache_0_3->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));

    cache = bus->processors[1]->getCache()[0];
    ui->cache_1_0->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[1]->getCache()[1];
    ui->cache_1_1->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[1]->getCache()[2];
    ui->cache_1_2->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[1]->getCache()[3];
    ui->cache_1_3->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));

    cache = bus->processors[2]->getCache()[0];
    ui->cache_2_0->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[2]->getCache()[1];
    ui->cache_2_1->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[2]->getCache()[2];
    ui->cache_2_2->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[2]->getCache()[3];
    ui->cache_2_3->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));

    cache = bus->processors[3]->getCache()[0];
    ui->cache_3_0->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[3]->getCache()[1];
    ui->cache_3_1->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[3]->getCache()[2];
    ui->cache_3_2->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
    cache = bus->processors[3]->getCache()[3];
    ui->cache_3_3->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                               .arg(cache.getAddress()).arg(+cache.getData()));
}

void MainWindow::updateMemory() {

}
