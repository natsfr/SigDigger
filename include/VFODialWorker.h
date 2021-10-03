#ifndef VFODIALWORKER_H
#define VFODIALWORKER_H

#include <QThread>
#include <cmath>
#include <libvfoknob/vfo_knob_lib.h>

class KnobInterface : public QThread{
    Q_OBJECT
public:
    KnobInterface(QWidget *parent = nullptr);
    ~KnobInterface();

    bool Init();
    void display(const uint16_t index, const char * data);

    void run() override;

private:
    hid_device * hknob;

    uint16_t buttons = 0;

signals:
    void incFreq(const qint64 delta);
};

#endif // VFODIALWORKER_H
