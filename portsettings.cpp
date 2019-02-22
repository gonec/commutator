#include "portsettings.h"

PortSettings::PortSettings()
{

}

int PortSettings::timeout() const {
    return mTimeout;
}
QSerialPort::BaudRate PortSettings::baudRate() const {
    return mBaudRate;
}
QString PortSettings::port() const {
    return mPort;
}

bool PortSettings::setTimeout( int timeout) {
    if( timeout<0 ) {
        mTimeout = 0;
        return false;
    }
    mTimeout = timeout;
    return true;
}
void PortSettings::setBaudRate(QSerialPort::BaudRate baudRate) {
    mBaudRate = baudRate;
}

void PortSettings::setBaudRate(QString strBaudRate) {
    mBaudRate = mBaudRates.fromQString(strBaudRate);
}
void PortSettings::setPort(const QString &name)  {
    mPort = name;
}

QString PortSettings::toString() const {
    return mPort + ":" + QString(mBaudRate);
}

bool PortSettings::isValid() const {
    return true;

}
