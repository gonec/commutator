#include "switcher.h"

Switcher::Switcher(QObject *parent) : QObject(parent)
{
    flAOpened = false;
    flBOpened = false;
    mPortBaccDroped=false;
    mPortAaccDroped=true;
    mComTimer = new QTimer();
    mComTimer->setSingleShot(true);
    mComTimer->setInterval(200);
    connect(mComTimer,SIGNAL(timeout()), this, SLOT(timeout()));
}

void Switcher::setComPorts(PortSettings aSett, PortSettings bSett){
    mSettA = aSett;
    mSettB = bSett;
}

void Switcher::connect_com() {
    qDebug()<<"Switcher::connect_com "<<" A:"<<mSettA.toString()<<" B:"<<mSettB.toString();
    mComAThread = new SlaveThread();
    mComBThread = new SlaveThread();

    //Подключение с ошибкой
    connect(mComAThread, SIGNAL(error(QString)), SLOT( connect_error(QString )) );
    connect(mComBThread, SIGNAL(error(QString)),
            SLOT( connect_error(QString )) );

    //Подключение успешно
    connect(mComAThread, SIGNAL( connected_ok() ), SLOT( connected_ok_a() ) );
    connect(mComBThread, SIGNAL( connected_ok() ), SLOT( connected_ok_b() ) );

    //Прочитаны данные
    connect(mComAThread, SIGNAL(raw_data_received(QByteArray)),
            SLOT( from_a(QByteArray )) );
    connect(mComBThread, SIGNAL(raw_data_received(QByteArray)),
            SLOT( from_b(QByteArray )) );
    connect(this, SIGNAL( close_a() ),  mComAThread, SLOT( close() ) );
    connect(this, SIGNAL( close_b() ),  mComBThread, SLOT( close() ) );
    connect(this, SIGNAL( to_b(QByteArray) ), mComBThread, SLOT( slot_send(QByteArray)) );
    connect(this, SIGNAL( to_a(QByteArray) ), mComAThread, SLOT( slot_send(QByteArray)) );
    connect( mComBThread, SIGNAL(port_closed()), SLOT(port_closed_a()) );
    connect( mComAThread, SIGNAL(port_closed()), SLOT(port_closed_b()) );
    flAOpened = false;
    flBOpened = false;
    mComAThread->startSlave(mSettA);
    mComBThread->startSlave(mSettB);
    flConnectError = false;
}

void Switcher::connect_error(QString comName) {
   emit sig_connect_error(comName);

   qDebug()<<"Switcher "<<"emiting close_a";
   emit close_a();

   qDebug()<<"Switcher "<<"emiting close_b";
   emit close_b();

}

void Switcher::connected_ok(QString portName, QSerialPort::BaudRate br) {

    qDebug()<<"connected ok"<<portName;
    emit sig_connect_success();
}

void Switcher::connected_ok_a() {
   flAOpened = true;
    emit sig_connect_success();


}
void Switcher::connected_ok_b() {
    flBOpened = true;
    emit sig_connect_success();


}
void Switcher::dropBdata() {
     emit from_com(QString("B"), mBacc);
     mBacc.clear();
     mPortBaccDroped = true;
}
void Switcher::dropAdata() {
     emit from_com(QString("A"), mAacc);
     mAacc.clear();
     mPortAaccDroped = true;
}

void Switcher::from_a(QByteArray a) {
    mComTimer->stop();

    mComTimer->start();
    mAacc += a;
    emit to_b(a);
    mPortAaccDroped = false;
    if (mPortBaccDroped) {

    }
    else {
        dropBdata();
    }
    qDebug()<<"from a"<<a;
}

void Switcher::from_b(QByteArray b){
    mComTimer->stop();
    mComTimer->start();
    mBacc+=b;
    emit to_a(b);
    mPortBaccDroped = false;
    if (mPortAaccDroped) {
    }
    else {
        dropAdata();
    }
    qDebug()<<"from b"<<b;
}

void Switcher::switch_ascii(bool fl){

}

void Switcher::disconnect() {
    qDebug()<<"SWITCHER::DISCONNECT --------";
    //ЗДЕСЬ МЫ ПАДАЕМ!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    if ( mComAThread->isRunning() && flAOpened ) {
        flAOpened = false;
        qDebug()<<"COM A is running. Terminating... ";
        emit close_a();
    }

    if ( mComBThread->isRunning() && flBOpened ) {
        flBOpened = false;
        qDebug()<<"COM B is running. Terminating... ";
        emit close_b();
    }
}

void Switcher::port_closed_a() {
    qDebug()<<"PORT CLOSED A";
    mComAThread->quit();
    qDebug()<<"waiting B ...";
    mComAThread->wait();
    qDebug()<<"A closed ...";

    delete mComAThread;
}

void Switcher::port_closed_b() {
    qDebug()<<"PORT CLOSED B";
    mComBThread->quit();
    qDebug()<<"waiting B ...";
    mComBThread->wait();
    qDebug()<<"B closed ...";
    delete mComBThread;
}

void Switcher::timeout(){
    qDebug()<<"TIMEOUT";
    if (!mPortAaccDroped ){
        dropAdata();
    }
    if (!mPortBaccDroped) {
        dropBdata();
    }
}


