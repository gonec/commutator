#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QSerialPortInfo>
#include <QDebug>
#include <QCheckBox>
#include <QString>
#include <QLabel>
#include "switcher.h"
#include "portsettings.h"
#include "baudrates.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QComboBox *cbA;
    QComboBox *cbB;
    QPushButton *pbCon;
    QPushButton *pbRescan;
    QTextBrowser *textBrowser;
    QGridLayout *gridLayout;
    QLabel *statusLabel;
    bool flConnected;
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QComboBox *cbBaudrateA;
    QComboBox *cbBaudrateB;
    QCheckBox *cbShowAscii;
    QPushButton *pbClear;
    QLabel *labelBrowser;
    QLabel *lbA;
    QLabel *lbB;
    QLabel *lbSpeedA;
    QLabel *lbSpeedB;
    Switcher *mSwitcher;
    void block_ports();

    void free_ports();
    void fill_ports() ;
    static const int NUM_SWITCHED = 2;
    //Пришло ли сообщение об ошибке
    int counter;
    bool flConnectTrigger;
signals:

public slots:
    void connect_ports();
    void disconnect_ports();
    //переключение в режим Ascii
    void switch_ascii(bool fl);

    //данные от com портов
    void from_com(QString name, QByteArray bt);

    //отображаем информацию о подключении
    void displayStatusInfo(QString);

    // Ошибка подключения
    void connect_error();
    void pb_connect_ports();
    // Подключение успешное
    void connect_success();

    void scan_ports();
    void disable_connection();
    void cb_a_activated(int);
    void cb_b_activated(int);
    void acceptPort(QComboBox *acceptor, QComboBox *donor, int index) ;
private:
    Ui::Widget *ui;
    bool flAscii;
    QList<QSerialPortInfo> mPortsA;
    QList<QSerialPortInfo> mPortsB;
};

#endif // WIDGET_H
