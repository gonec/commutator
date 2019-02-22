#ifndef BAUDRATES_H
#define BAUDRATES_H
#include <QStringList>
#include <QSerialPort>
#include <QString>
#include <QVector>
#include <QMap>

class Baudrates
{
public:
    Baudrates();
    QStringList baudsList() const ;
    QMap<QString, QSerialPort::BaudRate> mBaudRatesMap;
    QVector<QSerialPort::BaudRate> mBaudRates;
    QSerialPort::BaudRate fromQString(QString speed);
};

#endif // BAUDRATES_H
