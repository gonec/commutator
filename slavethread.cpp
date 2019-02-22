#include "slavethread.h"
#include <QTime>

QT_USE_NAMESPACE

SlaveThread::SlaveThread(QObject *parent)
    : QThread(parent), waitTimeout(0)
{
    qRegisterMetaType<QSerialPort::BaudRate>();
    moveToThread(this);

    log = new QFile( QString("terminal.txt") );
    if ( !log->open(QIODevice::Append | QIODevice::Text) )
           qDebug()<<"CAN NOT OPEN FILE";

    mSerial == nullptr;

}



void SlaveThread::startSlave(PortSettings portSettings)
{
    qDebug()<<"SlaveThread::starting slave!";

    this->mPortName = portSettings.port();
    this->waitTimeout = portSettings.timeout();
    qDebug()<<"SLAVE THREAD BAUD RATE"<<portSettings.baudRate();
    this->mBaudRate = portSettings.baudRate();
    start();

}

void SlaveThread::run()
{
    qDebug()<<"STARTING SLAVE THREAD "<<mPortName<<" : "<<mBaudRate;
    mSerial = new QSerialPort;
    mSerial->setPortName(mPortName);
    mSerial->setBaudRate(mBaudRate);

    if ( !mSerial->open(QIODevice::ReadWrite) ) {

        qDebug()<<"CAN NOT OPEN COM PORT"<<mSerial->error();
        emit error(QString("can not open %1").arg(mPortName));

    }
    else {
        qDebug()<<"SERIAL OPENED!";
        emit connected_ok(mPortName, mBaudRate);
        emit connected_ok();
        connect(mSerial, &QSerialPort::readyRead, this, &SlaveThread::handleReadyRead);

    }
    exec();
}

void SlaveThread::slot_send(QByteArray post) {
    int bt = mSerial->write( post );
    mSerial->flush();
    QDateTime dt;
    QTextStream out(log);
    out<< dt.currentDateTime().toString() <<post<<"  written:"<<bt<<"\n";
    //emit raw_data_send(post);
}

void SlaveThread::handleReadyRead() {

    QByteArray data = mSerial->readAll();
    qDebug()<<"received"<<data;
    //buff += data;
    emit raw_data_received(data);
    /*
    //emit raw_data_received(data);
    int pos=-1;

    while ( buff.indexOf(QString("]")) != -1 || buff.indexOf(QString(">")) != -1  ) {
        int pos_json = buff.indexOf(QString("]"));
        int pos_inner = buff.indexOf(QString(">"));
        if (pos_json  != -1 )
            pos = pos_json;
        if (pos_inner != -1 )
            pos = pos_inner;
        QByteArray msg = buff.left(pos+1);
        buff.remove( 0, pos+1 );
        QDateTime dt;
        QTextStream out(log);
        out<< dt.currentDateTime().toString() <<msg<<"\n";
        emit from_terminal( msg );
    }
    */
}
void SlaveThread::close() {

        if( mSerial!=nullptr ) {
            mSerial->close();
            delete mSerial;
            mSerial=nullptr;
            emit port_closed();
        }



}
