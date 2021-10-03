#include "UIMediator.h"
#include <cstring>

using namespace SigDigger;

void UIMediator::connectKnob() {
    connect(this->ui->ki,
            SIGNAL(incFreq(qint64)),
            this,
            SLOT(onFreqInc(qint64)));
}

void UIMediator::onFreqInc(const qint64 delta) {
    qint64 freq = this->ui->spectrum->getCenterFreq();
    freq += delta;
    this->ui->spectrum->setCenterFreq(freq);
    char feedback[64];
    std::sprintf(feedback, "%ld", freq);
    this->ui->ki->display(0, 0, (uint8_t *)feedback, std::strlen(feedback));
}
