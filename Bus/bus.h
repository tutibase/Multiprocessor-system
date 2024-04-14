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

public slots:
    // инвалидация всех ячеек в кэшах с данным адресом, кроме отправившего сигнал процессора
    void BusInvalidate(short lineAddress, int id);
    // переход всех ячеек в кэшах с данным адресом в состояние Shared
    void BusShared(short lineAddress);
};

#endif // BUS_H
