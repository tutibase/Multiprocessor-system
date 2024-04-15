#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bus = new Bus();

    ui->log->insertPlainText("MESIF protocol with \"least frequently used\" replacement policy:\n");

    CPULabels = {};

    for (int i = 0; i < processors_num; i++) {
        CacheLabels labels;
        for (int j = 0; j < cache_lines_num; j++) {
            labels.push_back(new QLabel("I"));
        }
        CPULabels.push_back(labels);
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

    for (int i = 0; i < cache_lines_num; i++) {
        ui->verticalLayout->addWidget(CPULabels[0][i]);
        ui->verticalLayout_2->addWidget(CPULabels[1][i]);
        ui->verticalLayout_3->addWidget(CPULabels[2][i]);
        ui->verticalLayout_4->addWidget(CPULabels[3][i]);
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
    for (int i = 0; i < processors_num; i++) {
        for (int j = 0; j < cache_lines_num; j++) {
            auto cache = bus->processors[i]->getCache()[j];
            CPULabels[i][j]->setText(QString("%1 | a%2 | %3").arg(cache.getState())
                                         .arg(cache.getAddress()).arg(+cache.getData()));
        }
    }

}

void MainWindow::updateMemory() {
    auto mem = bus->memory[0];
    ui->memory_0->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[1];
    ui->memory_1->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[2];
    ui->memory_2->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[3];
    ui->memory_3->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[4];
    ui->memory_4->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[5];
    ui->memory_5->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[6];
    ui->memory_6->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[7];
    ui->memory_7->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[8];
    ui->memory_8->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[9];
    ui->memory_9->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[10];
    ui->memory_10->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[11];
    ui->memory_11->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[12];
    ui->memory_12->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[13];
    ui->memory_13->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[14];
    ui->memory_14->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
    mem = bus->memory[15];
    ui->memory_15->setText(QString("a%1 | %2").arg(mem.getAddress()).arg(+mem.getData()));
}
