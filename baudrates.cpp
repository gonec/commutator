#include "baudrates.h"

Baudrates::Baudrates()
{
    /*
    QSerialPort::Baud1200	1200	1200 baud.
    QSerialPort::Baud2400	2400	2400 baud.
    QSerialPort::Baud4800	4800	4800 baud.
    QSerialPort::Baud9600	9600	9600 baud.
    QSerialPort::Baud19200	19200	19200 baud.
    QSerialPort::Baud38400	38400	38400 baud.
    QSerialPort::Baud57600	57600	57600 baud.
    QSerialPort::Baud115200	115200	115200 baud.
    */

   mBaudRatesMap.insert("1200",   QSerialPort::Baud1200  );
   mBaudRatesMap.insert("2400",   QSerialPort::Baud2400  );
   mBaudRatesMap.insert("4800",   QSerialPort::Baud4800  );
   mBaudRatesMap.insert("9600",   QSerialPort::Baud9600  );
   mBaudRatesMap.insert("19200",  QSerialPort::Baud19200 );
   mBaudRatesMap.insert("38400",  QSerialPort::Baud38400 );
   mBaudRatesMap.insert("57600",  QSerialPort::Baud57600 );
   mBaudRatesMap.insert("115200", QSerialPort::Baud115200);

    mBaudRates.append( QSerialPort::Baud1200  );
    mBaudRates.append( QSerialPort::Baud2400  );
    mBaudRates.append( QSerialPort::Baud4800  );
    mBaudRates.append( QSerialPort::Baud9600  );
    mBaudRates.append( QSerialPort::Baud19200 );
    mBaudRates.append( QSerialPort::Baud38400 );
    mBaudRates.append( QSerialPort::Baud57600 );
    mBaudRates.append( QSerialPort::Baud115200);
}

QStringList Baudrates::baudsList() const {
    QStringList baudList;
    for(int i=0; i < mBaudRates.size(); i++) {
        baudList<<QString::number( mBaudRates[i] );
    }
    return baudList;
}

QSerialPort::BaudRate Baudrates::fromQString(QString speed) {
    QMap<QString, QSerialPort::BaudRate >::const_iterator i = mBaudRatesMap.find(speed);
    if ( i != mBaudRatesMap.end() ) {
        return i.value();
    }

}
