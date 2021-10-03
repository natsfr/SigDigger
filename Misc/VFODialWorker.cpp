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
    }
}
