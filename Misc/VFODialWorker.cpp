#include <cstring>
#include <VFODialWorker.h>

KnobInterface::KnobInterface(QWidget *parent) {

}

KnobInterface::~KnobInterface() {
    if(this->hknob != 0) close_hid(this->hknob);
}

bool KnobInterface::Init() {
    this->hknob = open_by_id(0x2341, 0x8036, NULL);
    if(this->hknob == 0) {
        return false;
    }
    return true;
}

void KnobInterface::display(uint8_t x, uint8_t y, uint8_t *str, uint8_t len) {
    mutex.lock();
    this->x = x;
    this->y = y;
    this->displayChanged = true;
    this->txtLen = len;
    std::strncpy((char *)this->displayText, (char *)str, 64);
    mutex.unlock();
}

void KnobInterface::run() {
    int16_t basic_divider = 0;
    int16_t delta = 0;
    while(true) {
        HID_VFO_Report * pReport = read_report(this->hknob);
        basic_divider += pReport->smooth;
        if(basic_divider > 150) {
            delta++;
            emit(incFreq(100));
            basic_divider = 0;
        } else if(basic_divider < -150) {
            delta--;
            emit(incFreq(-100));
            basic_divider = 0;
        }
        mutex.lock();
        if(displayChanged) {
            // Size fixed at 61 for 64byte report
            send_text(this->hknob, this->x, this->y, this->displayText, 61);
            displayChanged = false;
        }
        mutex.unlock();
    }
}
