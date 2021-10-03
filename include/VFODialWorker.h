#ifndef VFODIALWORKER_H
#define VFODIALWORKER_H

#include <QThread>
#include <QMutex>
#include <cmath>
#include <libvfoknob/vfo_knob_lib.h>

class KnobInterface : public QThread{
    Q_OBJECT
public:
    KnobInterface(QWidget *parent = nullptr);
    ~KnobInterface();

    bool Init();
    void display(uint8_t x, uint8_t y, uint8_t *str, uint8_t len);

    void run() override;

private:
    hid_device * hknob;

    uint16_t buttons = 0;
    uint64_t increment = 10;

    QMutex mutex;

    uint8_t x,y;
    bool displayChanged;
    uint8_t displayText[64];
    uint8_t txtLen;

signals:
    void incFreq(const qint64 delta);
};

#endif // VFODIALWORKER_H
