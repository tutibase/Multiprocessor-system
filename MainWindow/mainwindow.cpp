#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bus = new Bus();
    bus_cycles = 0;

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
        QObject::connect(bus->processors[i], &Processor::endBusCycle,
                         this, &MainWindow::increaseBusCycles);
    }

    ui->verticalLayout->addWidget(new QLabel("Section 0"));
    ui->verticalLayout_2->addWidget(new QLabel("Section 0"));
    ui->verticalLayout_3->addWidget(new QLabel("Section 0"));
    ui->verticalLayout_4->addWidget(new QLabel("Section 0"));
    for (int i = 0; i < cache_lines_num; i++) {
        if (i == cache_lines_num / 2) {
            ui->verticalLayout->addWidget(new QLabel("Section 1"));
            ui->verticalLayout_2->addWidget(new QLabel("Section 1"));
            ui->verticalLayout_3->addWidget(new QLabel("Section 1"));
            ui->verticalLayout_4->addWidget(new QLabel("Section 1"));
        }
        ui->verticalLayout->addWidget(CPULabels[0][i]);
        ui->verticalLayout_2->addWidget(CPULabels[1][i]);
        ui->verticalLayout_3->addWidget(CPULabels[2][i]);
        ui->verticalLayout_4->addWidget(CPULabels[3][i]);
    }

    for (int i = 0; i < memory_cells_num; i++) {
        memory_labels.push_back(new QLabel(QString("address: a%1, data: 0").arg(i)));
        if (i < memory_cells_num / 2) {
            ui->verticalLayout_5->addWidget(memory_labels[i]);
        }
        else {
            ui->verticalLayout_6->addWidget(memory_labels[i]);
        }
    }

    QObject::connect(bus, &Bus::updateLog,
                     this, &MainWindow::updateLog);
    QObject::connect(bus, &Bus::updateCacheView, this, &MainWindow::updateCache);
    QObject::connect(bus, &Bus::updateMemoryView, this, &MainWindow::updateMemory);

    QObject::connect(bus, &Bus::endBusCycle, this, &MainWindow::increaseBusCycles);
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
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(0, Clicking::Read), address));
    }
    else {
        bus->processors[0]->readLine(address);
    }
}

void MainWindow::on_write_0_clicked() {
    int address = ui->comboBox_0->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(0, Clicking::Write), address));
    }
    else {
        bus->processors[0]->writeLine(address);
    }
}




void MainWindow::on_read_1_clicked() {
    int address = ui->comboBox_1->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(1, Clicking::Read), address));
    }
    else {
        bus->processors[1]->readLine(address);
    }
}

void MainWindow::on_write_1_clicked() {
    int address = ui->comboBox_1->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(1, Clicking::Write), address));
    }
    else {
        bus->processors[1]->writeLine(address);
    }
}



void MainWindow::on_read_2_clicked() {
    int address = ui->comboBox_2->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(2, Clicking::Read), address));
    }
    else {
        bus->processors[2]->readLine(address);
    }
}

void MainWindow::on_write_2_clicked() {
    int address = ui->comboBox_2->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(2, Clicking::Write), address));
    }
    else {
        bus->processors[2]->writeLine(address);
    }
}



void MainWindow::on_read_3_clicked() {
    int address = ui->comboBox_3->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(3, Clicking::Read), address));
    }
    else {
        bus->processors[3]->readLine(address);
    }
}

void MainWindow::on_write_3_clicked() {
    int address = ui->comboBox_3->currentIndex();
    if (ui->sim_call_box->checkState() == Qt::CheckState::Checked) {
        callings.push_back(QPair<Caller, int>(Caller(3, Clicking::Write), address));
    }
    else {
        bus->processors[3]->writeLine(address);
    }
}

void MainWindow::updateCache() {
    for (int i = 0; i < processors_num; i++) {
        for (int j = 0; j < cache_lines_num; j++) {
            auto cache = bus->processors[i]->getCache()[j];
            if (cache.getAddress() == -1)
                CPULabels[i][j]->setText(QString("I"));
            else {
                std::bitset<4> addr_tag(cache.getAddress());
                CPULabels[i][j]->setText(QString("%1 | %2 | %3\t\taddress: a%4").arg(cache.getState())
                                             .arg(QString::fromStdString(addr_tag.to_string()))
                                             .arg(+cache.getData())
                                             .arg(cache.getAddress()));
            }
        }
    }

}

void MainWindow::updateMemory() {
    for (int i = 0; i < memory_cells_num; i++) {
        auto mem = bus->memory[i];
        memory_labels[i]->setText(QString("address: a%1, data: %2").arg(i).arg(+mem.getData()));
    }
}

void MainWindow::on_sim_call_box_stateChanged(int state)
{
    if (state == Qt::CheckState::Unchecked) callings.clear();
}


void MainWindow::on_confirm_button_clicked()
{
    if (ui->sim_call_box->checkState() == Qt::CheckState::Unchecked) return;
    for (auto &call : callings) {
        int processor_id = call.first.first;
        Clicking operation = call.first.second;
        int address = call.second;
        if (operation == Clicking::Read) bus->processors[processor_id]->readLine(address);
        else bus->processors[processor_id]->writeLine(address);
    }
    callings.clear();
}

void MainWindow::increaseBusCycles() {
    ui->bus_cycles_label->setText("Bus cycles: " + QString::number(++bus_cycles));
}
