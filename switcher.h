#ifndef SWITCHER_H
#define SWITCHER_H

#include <QObject>
#include "portsettings.h"
#include <QDebug>
#include <QTimer>
#include "slavethread.h"
class Switcher : public QObject
{
    Q_OBJECT
public:
    explicit Switcher(QObject *parent = nullptr);
    SlaveThread *mComAThread;
    SlaveThread *mComBThread;
    PortSettings mSettA;
    PortSettings mSettB;
    bool flConnectError;
    bool flAOpened;
    bool flBOpened;
    QByteArray mAacc;
    QByteArray mBacc;
    bool mPortAaccDroped;
    bool mPortBaccDroped;
    QTimer *mComTimer;
signals:
    void from_com(QString name, QByteArray val);
    void to_a(QByteArray b);
    void to_b(QByteArray a);
    void sig_connect_error(QString);
    void sig_connect_success();
    void close_a();
    void close_b();
public slots:
    void setComPorts(PortSettings a, PortSettings b);
    void connect_com();
    //Ошибка подсоединения @comName - имя ком порта
    void connect_error(QString comName);
    void connected_ok(QString portName, QSerialPort::BaudRate br);
    void from_a(QByteArray);
    void from_b(QByteArray);
    void switch_ascii(bool f);
    void connected_ok_a();
    void connected_ok_b();
    void disconnect();
    void port_closed_a();
    void port_closed_b();
    void dropBdata();
    void dropAdata();
    void timeout();
};

#endif // SWITCHER_H
