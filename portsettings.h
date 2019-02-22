#ifndef PORTSETTINGS_H
#define PORTSETTINGS_H
#include <QString>
#include <QSerialPort>
#include "baudrates.h"

class PortSettings
{
public:
    PortSettings();
    QSerialPort::BaudRate baudRate() const;
    //имя ком порта
    QString port() const;
    int timeout() const;
    bool setTimeout( int timeout) ;

    void setBaudRate(QSerialPort::BaudRate baudRate) ;
    void setBaudRate(QString strBaudRate);
    void setPort(const QString &name);
    //настройки в текстовом виде (для отладки)
    QString toString() const;
    //Проверяем установлены ли настройки
    bool isValid() const;
private:
    QString mPort;
    QSerialPort::BaudRate mBaudRate;
    int mTimeout;
    Baudrates mBaudRates;
};

#endif // PORTSETTINGS_H
