#ifndef BUS_H
#define BUS_H
#include "../Processor/processor.h"
#include "../Memory/memoryline.h"

class Bus : public QObject {
    Q_OBJECT
public:
    Bus();

    std::vector<Processor*> processors; // все процессоры в системе
    std::vector<MemoryLine> memory; // память в системе

signals:
    void updateLog(QString msg); // сообщение в лог
    void updateCacheView();
    void updateMemoryView();
    void endBusCycle();

public slots:
    // инвалидация всех ячеек в кэшах с данным адресом, кроме отправившего сигнал процессора
    void BusInvalidate(short lineAddress, int id);
    // перезапись строки cache_line_num в кэше процессора id
    void writeDataToCache(int id, short cache_line_num, short lineAddress, char data, char state);
    void writeDataToMemory(short lineAddress, char data);

    // чтение в кэш процессора ячейки памяти из остальных кэшей / памяти
    void BusRead(short lineAddress, int id);
    void BusRWITM(short lineAddress, int id);

    void updateLogSlot(QString msg) { emit updateLog(msg); } // промежуточное звено между процессором и логом
};

#endif // BUS_H
