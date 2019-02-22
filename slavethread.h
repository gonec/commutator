#ifndef SLAVETHREAD_H
#define SLAVETHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include "portsettings.h"
#include <QFile>
#include <QMutex>
class SlaveThread : public QThread
{
    Q_OBJECT

public:
    explicit SlaveThread(QObject *parent = 0);


    void startSlave(PortSettings );
    void run() Q_DECL_OVERRIDE;

    QSerialPort *mSerial;

signals:
    //высокоуровневое сообщение
    void high_level(QString);
    void to_at(QString );
    void from_at(QString);
    void error(const QString &s);
    void timeout(const QString &s);
    void from_terminal(QByteArray);
    void connected_ok(QString port, QSerialPort::BaudRate);
     void connected_ok();
    void raw_data_received(QByteArray raw);
    void raw_data_send(QByteArray raw);
    void port_closed();
public slots:
    void close();
    void slot_send(QByteArray msg);
    void handleReadyRead();
public:
     QByteArray buff;

private:
    QString mPortName;
    QSerialPort::BaudRate mBaudRate;
    QMutex serialLocker;
    int waitTimeout;


    QFile *log;
};



#endif // SLAVETHREAD_H
