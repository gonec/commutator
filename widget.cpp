#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    gridLayout = new QGridLayout();
    bool flAscii = true;

    hLayout = new QHBoxLayout();
    vLayout = new QVBoxLayout();
    cbA = new QComboBox();
    cbB = new QComboBox();
    cbBaudrateA = new QComboBox();
    cbBaudrateB = new QComboBox();
    Baudrates bd;
    cbBaudrateA->addItems( bd.baudsList() );
    cbBaudrateB->addItems( bd.baudsList() );
    QString preferedBaudRate = "115200";
    int idx = cbBaudrateA->findText(preferedBaudRate);
    if ( idx != -1 ) {
        cbBaudrateA->setCurrentIndex(idx);
        cbBaudrateB->setCurrentIndex(idx);
    }

    pbRescan =  new QPushButton();
    pbRescan->setText( QString("Обновить список портов") );

    flConnected = false;




    pbCon = new  QPushButton();
    pbCon->setText( QString("Соединить") );
    lbA = new QLabel("Первый порт");
    lbB = new QLabel("Второй порт");
    lbSpeedA = new QLabel("Скорость бод");
    lbSpeedB = new QLabel("Скорость бод");
    int start_row = 0;
    int first_column = 0;
    int second_column = 1;
    gridLayout->addWidget(lbA, start_row, first_column);
    gridLayout->addWidget(lbB, start_row, second_column);
    gridLayout->addWidget(cbA, ++start_row, first_column);
    gridLayout->addWidget(cbB, start_row, second_column);

    gridLayout->addWidget(lbSpeedA, ++start_row, first_column);
    gridLayout->addWidget(lbSpeedB, start_row, second_column);

    gridLayout->addWidget(cbBaudrateA, ++start_row, first_column);
    gridLayout->addWidget(cbBaudrateB, start_row, second_column);
    gridLayout->addWidget(pbCon);
    gridLayout->addWidget(pbRescan);
    cbShowAscii = new QCheckBox( QString("Отображать в ASCII") );
    statusLabel = new QLabel();
    pbClear = new QPushButton();
    vLayout->addLayout(gridLayout);
    setLayout(vLayout);
    setWindowTitle( QString("Коммутатор портов") );
    hLayout->addWidget(cbShowAscii);
    pbClear->setText( QString("Очистить окно обмена") );
    hLayout->addWidget(pbClear);
    hLayout->addWidget(statusLabel);
    vLayout->addLayout(hLayout);
    labelBrowser = new QLabel("Окно обмена");
    textBrowser = new QTextBrowser();
    vLayout->addWidget(labelBrowser);
    vLayout->addWidget(textBrowser);

    gridLayout->setSpacing(5);
    //Минимальное кол-во COM портов
    const int MINIMUM_COM_NUM = 2;
    connect(pbCon, SIGNAL( clicked() ), this, SLOT(pb_connect_ports()));
    connect(pbRescan, &QPushButton::clicked, [=]() {
         if (flConnected) {
             qDebug()<<"RESCAN DISCONNECT PORTS";
             disconnect_ports();
         }
         scan_ports();
         fill_ports();
         if ( mPortsA.size() >= MINIMUM_COM_NUM ) {
             pbCon->setEnabled(true);
             free_ports();
         }
         else {
             pbCon->setEnabled(false);
             textBrowser->append("Подключите дополнительные COM устройства...");
         }
      }
     );
     mSwitcher = new Switcher();
     connect(mSwitcher, SIGNAL(from_com(QString, QByteArray)), this, SLOT(from_com(QString, QByteArray)));
     connect(mSwitcher, SIGNAL(sig_connect_success()), this, SLOT(connect_success()));
     //displayStatusInfo(QString("Информация"));
     connect(cbShowAscii, SIGNAL(clicked(bool)), this, SLOT(switch_ascii(bool)));
     connect( pbClear, &QPushButton::clicked,[=]()
     {
         textBrowser->clear();
     });

     counter = 0;
     flConnectTrigger = true;
     cbShowAscii->setChecked(flAscii);

     scan_ports();
     fill_ports();
     if (mPortsA.size() >= MINIMUM_COM_NUM ) {

     }
     else {
         block_ports();
          textBrowser->append("Подключите дополнительные COM устройства...");
     }

     ( mPortsA.size() >= MINIMUM_COM_NUM ) ? pbCon->setEnabled(true) : pbCon->setEnabled(false);
     connect(cbA, SIGNAL(currentIndexChanged(int )), SLOT( cb_a_activated(int) ) );
     connect(cbB, SIGNAL(currentIndexChanged(int )), SLOT( cb_b_activated(int) ) );
}
void Widget::fill_ports() {
    cbA->clear();
    cbB->clear();
    QString portA;
    for (int i=0; i < mPortsA.size(); ++i) {
        if (i==0) {
            portA = mPortsA[0].portName();
            cbA->setCurrentIndex(0);
        }
        cbA->addItem( mPortsA[i].portName() );
    }
    QStringList ports;
    for (int i =0; i < mPortsB.size(); ++i) {
        if ( mPortsB[i].portName() == portA ) {

        }
        else {
              cbB->addItem( mPortsB[i].portName() );
        }
    }

}
void Widget::pb_connect_ports(){
    if (flConnectTrigger) {
        qDebug()<<"CONNECTING PORTS";

        connect_ports();
    }
    else {
        qDebug()<<"DISCONNECTING PORTS";
        disconnect_ports();
        flConnectTrigger = true;
    }

}
void Widget::connect_ports() {
    counter =0;
    QString portNameA = cbA->currentText();
    QString portNameB = cbB->currentText();
    //QString baudA = b
    PortSettings settA;
    PortSettings settB;
    QString strBaudRateA = cbBaudrateA->currentText();
    QString strBaudRateB = cbBaudrateB->currentText();

    settA.setPort( portNameA );
    settB.setPort( portNameB );

    settA.setBaudRate( strBaudRateA );
    settB.setBaudRate( strBaudRateB );

    //settA.setBaudRate()
    bool validA = settA.isValid();
    bool validB = settB.isValid();
    if (validA && validB) {
        mSwitcher->setComPorts(settA, settB);
        mSwitcher->connect_com();
    }
}
void Widget::from_com(QString name, QByteArray bt) {
    QString color;
    if (name =="A") {
        name = cbA->currentText();
        color="<b style=\"color:red;\">";
    }
    else {
        color="<b style=\"color:blue;\">";
        name = cbB->currentText();
    }
    if (flAscii) {
        textBrowser->append(name + " : " + color + QString::fromLatin1( bt.data() ) +"</b>" );
    }
    else {
        textBrowser->append(name + " : " + bt.toHex());
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::block_ports() {
    cbA->setEnabled(false);
    cbB->setEnabled(false);
    cbBaudrateA->setEnabled(false);
    cbBaudrateB->setEnabled(false);
    flConnectTrigger = false;

}

void Widget::disable_connection() {
    cbA->setEnabled(false);
    cbB->setEnabled(false);
    cbBaudrateA->setEnabled(false);
    cbBaudrateB->setEnabled(false);
    flConnectTrigger = false;
    pbCon->setText("Разъединить");
    pbCon->setEnabled("false");
}

void Widget::free_ports() {
    cbA->setEnabled(true);
    cbB->setEnabled(true);
    cbBaudrateA->setEnabled(true);
    cbBaudrateB->setEnabled(true);
    //поведение кнопки
    flConnectTrigger = true;
    pbCon->setText("Соединить");
}

void Widget::switch_ascii(bool flState) {
    flAscii = flState;
}

void Widget::displayStatusInfo(QString info) {
    statusLabel->setText(info);
}

void Widget::connect_error() {


}

void Widget::connect_success() {
    counter++;
    if (counter == 2) {
        flConnected = true;
        flConnectTrigger = false;
        disable_connection();
         textBrowser->append(QString("Соединение установлено..."));
    }

}

void Widget::disconnect_ports() {
    counter=0;
    flConnected = false;
    qDebug()<<"Widget::disconnect_ports";
    mSwitcher->disconnect();
    qDebug()<<"FREE PORTS";
    free_ports();
}

void Widget::scan_ports() {
    mPortsA.clear();
    mPortsB.clear();
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        mPortsA.append(info);

    }
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        mPortsB.append(info);
    }

};

void Widget::acceptPort(QComboBox *accepter, QComboBox *donor, int index) {
    cbB->disconnect();
    cbA->disconnect();

    QString portAccepterText = accepter->itemText(index);
    QString portDonorOldText = donor->currentText();
    donor->clear();
    for (int i =0; i < mPortsB.size(); ++i) {
        if ( mPortsB[i].portName()!=portAccepterText) {
                  donor->addItem( mPortsB[i].portName() );
            }
        }
    int new_index = accepter->findText(portAccepterText);
    accepter->setCurrentIndex(new_index);

    //если мы забрали из b порт
    if (portAccepterText == portDonorOldText) {
        //такого быть не может
    }
    else{
        //а если не забрали, то восстановим
        donor->setCurrentIndex(donor->findText(portDonorOldText) );
    }
    connect(cbB, SIGNAL(currentIndexChanged(int )), SLOT( cb_b_activated(int) ) );
    connect(cbA, SIGNAL(currentIndexChanged(int )), SLOT( cb_a_activated(int) ) );
}

void Widget:: cb_a_activated(int index) {
    //а забирает выбранный порт у Б
    acceptPort(cbA, cbB, index);


}

void Widget:: cb_b_activated(int index) {
      //б забирает выбранный порт у А
    acceptPort(cbB, cbA, index);

}
