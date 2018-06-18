#include "dose.h"
#include "ui_dose.h"
//#include "qextserialport.h"
//#include "qextserialenumerator.h"
#include <QtSerialPort/QSerialPortInfo>
#include "hled.h"
#include "qmessagebox.h"
#include <QQuickView>


dose::dose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dose)
{
    ui->setupUi(this);
    setWindowTitle(tr("Doser"));
    setWindowIcon (QIcon(":/ico/dosing_icon.jpg"));
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->cbCom->addItem(info.portName());
    connect(&thread, &MasterThread::response, this, &dose::showResponse);
    connect(&thread, &MasterThread::error, this, &dose::processError);
    connect(&thread, &MasterThread::timeout, this, &dose::processTimeout);
    jsonParserErrorCounter = 0;
    ui->led->turnOff();
    ui->ledLAN->turnOff();
    Syncronize = new QTimer(this);
    Syncronize->setInterval(1000);
    ui->cbnpump->addItem("0");
    ui->cbnpump->addItem("1");
    ui->cbnpump->addItem("2");
    ui->cbnpump->addItem("3");
    ui->cbnline_3->addItem("0");
    ui->cbnline_3->addItem("1");
    ui->cbnline_3->addItem("2");
    ui->cbnline_3->addItem("3");


    QQuickView *view = new QQuickView();
    QWidget *container;
    container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    container->setAutoFillBackground(true);
    container->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line1->addWidget(container);
    tankLevelObject1 = (QObject*)view->rootObject();

    QQuickView *view2 = new QQuickView();
    QWidget *container2;
    container2 = QWidget::createWindowContainer(view2, this);
    container2->setFocusPolicy(Qt::TabFocus);
    container2->setAutoFillBackground(true);
    container2->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view2->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line2->addWidget(container2);
    tankLevelObject2 = (QObject*)view2->rootObject();


    QQuickView *view3 = new QQuickView();
    QWidget *container3;
    container3 = QWidget::createWindowContainer(view3, this);
    container3->setFocusPolicy(Qt::TabFocus);
    container3->setAutoFillBackground(true);
    container3->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view3->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line3->addWidget(container3);
    tankLevelObject3 = (QObject*)view3->rootObject();

    QQuickView *view4 = new QQuickView();
    QWidget *container4;
    container4 = QWidget::createWindowContainer(view4, this);
    container4->setFocusPolicy(Qt::TabFocus);
    container4->setAutoFillBackground(true);
    container4->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view4->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line4->addWidget(container4);
    tankLevelObject4 = (QObject*)view4->rootObject();

    QQuickView *view5 = new QQuickView();
    QWidget *container5;
    container5 = QWidget::createWindowContainer(view5, this);
    container5->setFocusPolicy(Qt::TabFocus);
    container5->setAutoFillBackground(true);
    container5->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view5->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line5->addWidget(container5);
    tankLevelObject5 = (QObject*)view5->rootObject();

    QQuickView *view6 = new QQuickView();
    QWidget *container6;
    container6 = QWidget::createWindowContainer(view6, this);
    container6->setFocusPolicy(Qt::TabFocus);
    container6->setAutoFillBackground(true);
    container6->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view6->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line6->addWidget(container6);
    tankLevelObject6 = (QObject*)view6->rootObject();

    QQuickView *view7 = new QQuickView();
    QWidget *container7;
    container7 = QWidget::createWindowContainer(view7, this);
    container7->setFocusPolicy(Qt::TabFocus);
    container7->setAutoFillBackground(true);
    container7->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view7->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line7->addWidget(container7);
    tankLevelObject7 = (QObject*)view7->rootObject();

    QQuickView *view8 = new QQuickView();
    QWidget *container8;
    container8 = QWidget::createWindowContainer(view8, this);
    container8->setFocusPolicy(Qt::TabFocus);
    container8->setAutoFillBackground(true);
    container8->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
    view8->setSource(QUrl("qrc:/QML/main.qml"));
    ui->vl_line8->addWidget(container8);
    tankLevelObject8 = (QObject*)view8->rootObject();




    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    // You may want to use QRegularExpression for new code with Qt 5 (not mandatory).
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->leIP1->setValidator(ipValidator);
    ui->leNet1->setValidator(ipValidator);
    ui->leGate1->setValidator(ipValidator);

    //Tolgo il tab della linea slave
    widgetSlave = ui->twMenu->widget(4);
    ui->twMenu->removeTab(4);
    ui->lline5_1->hide();
    ui->llvalue5_1->hide();
    ui->lline5_2->hide();
    ui->llvalue5_2->hide();
    ui->lline5_3->hide();
    ui->llvalue5_3->hide();
    ui->lline5_4->hide();
    ui->llvalue5_4->hide();
    ui->lline5_5->hide();
    ui->llvalue5_5->hide();
    ui->lline5_6->hide();
    ui->llvalue5_6->hide();
    ui->lline5_7->hide();
    ui->llvalue5_7->hide();

    ui->lline6_1->hide();
    ui->llvalue6_1->hide();
    ui->lline6_2->hide();
    ui->llvalue6_2->hide();
    ui->lline6_3->hide();
    ui->llvalue6_3->hide();
    ui->lline6_4->hide();
    ui->llvalue6_4->hide();
    ui->lline6_5->hide();
    ui->llvalue6_5->hide();
    ui->lline6_6->hide();
    ui->llvalue6_6->hide();
    ui->lline6_7->hide();
    ui->llvalue6_7->hide();

    ui->lline7_1->hide();
    ui->llvalue7_1->hide();
    ui->lline7_2->hide();
    ui->llvalue7_2->hide();
    ui->lline7_3->hide();
    ui->llvalue7_3->hide();
    ui->lline7_4->hide();
    ui->llvalue7_4->hide();
    ui->lline7_5->hide();
    ui->llvalue7_5->hide();
    ui->lline7_6->hide();
    ui->llvalue7_6->hide();
    ui->lline7_7->hide();
    ui->llvalue7_7->hide();

    ui->lline8_1->hide();
    ui->llvalue8_1->hide();
    ui->lline8_2->hide();
    ui->llvalue8_2->hide();
    ui->lline8_3->hide();
    ui->llvalue8_3->hide();
    ui->lline8_4->hide();
    ui->llvalue8_4->hide();
    ui->lline8_5->hide();
    ui->llvalue8_5->hide();
    ui->lline8_6->hide();
    ui->llvalue8_6->hide();
    ui->lline8_7->hide();
    ui->llvalue8_7->hide();

    QDate currDate;
    QTime currTime;
    currDate = QDate::currentDate();
    currTime = QTime::currentTime();
    ui->dateTimeEdit->setDate(currDate);
    ui->dateTimeEdit->setTime(currTime);

    connect(Syncronize, SIGNAL(timeout()), SLOT(Sync()));
    ui->pbDosing->hide();
    ui->pbDatamoving->hide();
    //Gestione DB Dati da immagazzinare
    StorageDB = QSqlDatabase::addDatabase("QSQLITE");
    QString dbSPath = QCoreApplication::applicationDirPath() + "/doser.db";
    StorageDB.setDatabaseName(dbSPath);
    if (!StorageDB.open())
    {
        QString err_support;
        err_support = StorageDB.lastError().text();
        QMessageBox::critical(this, tr(TITLE_APP),
                              tr("Impossibile aprire il database o eseguire la query")+
                              err_support+tr("\nClick Cancel per uscire.")
                              , QMessageBox::Cancel);
    }
    qDebug()<<"Creazione tabelle database!";
    //Creo tabella DB
    QSqlQuery query;
    query.exec("create table if not exists timerDose( \
               id INTEGER PRIMARY KEY NOT NULL, \
               time SMALLTIME NOT NULL, \
               id_line INTEGER NOT NULL, \
               quantity FLOAT NOT NULL, \
               dayOfWek INTEGER, \
               row INTEGER)");
            if(query.lastError().isValid())
            qDebug()<<query.lastError();
    query.exec("create table if not exists line( \
               id INTEGER PRIMARY KEY NOT NULL, \
               id_pump INTEGER NOT NULL, \
               capacity FLOAT NOT NULL, \
               level FLOAT NOT NULL, \
               abilitation INTEGER, \
               timer_abilitation INTEGER, \
               description VARCHAR(25)\
               )");
            if(query.lastError().isValid())
            qDebug()<<query.lastError();
    query.exec("create table if not exists settings( \
               fact_calibration DOUBLE NOT NULL, \
               id_pump INTEGER PRIMARY KEY NOT NULL)");
            if(query.lastError().isValid())
            qDebug()<<query.lastError();

    qDebug()<<"Inizializzazione tabelle database!\n";
    //InitDB
    int u = 0;
    for(u = 0;u < NUM_OF_PUMP; u++)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO settings VALUES(?,?)");
        query.bindValue(0, 2000);
        query.bindValue(1, u);
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();
    }
    for(u = 0;u < NUM_OF_SCHEDULER; u++)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO timerDose VALUES(?,?,?,?,?,?)");
        query.bindValue(0, u);
        query.bindValue(1, 0);
        query.bindValue(2, 0);
        query.bindValue(3, 0);
        query.bindValue(4, 0);
        query.bindValue(5, 255);
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();

    }
    for(u = 0;u < NUM_OF_PUMP; u++)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO line VALUES(?,?,?,?,?,?,?)");
        query.bindValue(0, u);
        query.bindValue(1, 0);
        query.bindValue(2, 0);
        query.bindValue(3, 0);
        query.bindValue(4, 0);
        query.bindValue(5, 0);
        query.bindValue(6, ("Soluzione"));
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();
    }
    Syncronize->start();
    ui->statusBar->showMessage("Ready!");
    //    ui->pbResidualSol_2->setRange(0, 100);
    //ui->pbResidualSol_3->setRange(0, 100);
    //ui->pbResidualSol_4->setRange(0, 100);
    //ui->pbResidualSol_5->setRange(0, 100);
    ui->pbDatamoving->setRange(0, NUM_OF_SCHEDULER);

    //carico valori  da db delle line
    UpdateLine();
    //popolo il campo di calibrazione della tabella dosaggio manuale
    query.prepare("SELECT fact_calibration FROM settings WHERE id_pump = ?");
    query.bindValue(0, ui->cbnpump->currentIndex());
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    while (query.next())
    {
        double out = query.value(0).toDouble();
        ui->dscalibrate->setValue(out);
    }
    ReadLineStatus = 0;
   // SendConfiguration = 0;
    for(u = 0; u < 7; u++)
        ui->twProg->setColumnWidth(u, 150);

    QDoubleValidator *myDblVal = new QDoubleValidator(0.1, 9999, 2, this);
    myDblVal->setNotation(QDoubleValidator::StandardNotation);
    //ui->leQuantity->setInputMask("0.00");
    //ui->leQuantity->setMaxLength(4);
    ui->leQuantity->setValidator(myDblVal);
    ui->leQuantity_3->setValidator(myDblVal);

    ui->cbAbleSol_2->setEnabled(false);
    ui->cbAbleTimeSol_2->setEnabled(false);
    ui->leCapacitySol_2->setEnabled(false);
    ui->pbRefilSol_2->setEnabled(false);
    //we color in grey tank
    QObject *bar = tankLevelObject1->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", true);
    //    ui->pbResidualSol_2->setEnabled(false);
    qDebug()<<"Point A";
    ui->cbAbleSol_3->setEnabled(false);
    ui->cbAbleTimeSol_3->setEnabled(false);
    ui->leCapacitySol_3->setEnabled(false);
    ui->pbRefilSol_3->setEnabled(false);
    //we color in grey tank

    bar = tankLevelObject2->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_3->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }
    ui->cbAbleSol_4->setEnabled(false);
    ui->cbAbleTimeSol_4->setEnabled(false);
    ui->leCapacitySol_4->setEnabled(false);
    ui->pbRefilSol_4->setEnabled(false);
    //we color in grey tank
    bar = tankLevelObject3->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_4->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->cbAbleSol_5->setEnabled(false);
    ui->cbAbleTimeSol_5->setEnabled(false);
    ui->leCapacitySol_5->setEnabled(false);
    ui->pbRefilSol_5->setEnabled(false);
    //we color in grey tank
    bar = tankLevelObject4->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_5->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->cbAbleSol_6->setEnabled(false);
    ui->cbAbleTimeSol_6->setEnabled(false);
    ui->leCapacitySol_6->setEnabled(false);
    ui->pbRefilSol_6->setEnabled(false);
    bar = tankLevelObject5->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_6->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->cbAbleSol_7->setEnabled(false);
    ui->cbAbleTimeSol_7->setEnabled(false);
    ui->leCapacitySol_7->setEnabled(false);
    ui->pbRefilSol_7->setEnabled(false);
    bar = tankLevelObject6->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_7->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->cbAbleSol_8->setEnabled(false);
    ui->cbAbleTimeSol_8->setEnabled(false);
    ui->leCapacitySol_8->setEnabled(false);
    ui->pbRefilSol_8->setEnabled(false);
    bar = tankLevelObject7->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_8->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->cbAbleSol_9->setEnabled(false);
    ui->cbAbleTimeSol_9->setEnabled(false);
    ui->leCapacitySol_9->setEnabled(false);
    ui->pbRefilSol_9->setEnabled(false);
    bar = tankLevelObject8->findChild<QObject*>("tank");
    if (bar)
    {
        if(ui->cbAbleSol_9->isChecked())
        {
            bar->setProperty("enable", true);
        }
        else
        {
            bar->setProperty("enable", false);
        }
    }

    ui->led_line_1->turnOn(0);
    ui->led_line_2->turnOn(0);
    ui->led_line_3->turnOn(0);
    ui->led_line_4->turnOn(0);
    ui->led_line_5->turnOn(0);
    ui->led_line_6->turnOn(0);
    ui->led_line_7->turnOn(0);
    ui->led_line_8->turnOn(0);

    ui->tbStdOut->hide();
    ui->statusLabel->hide();
    ui->pbStdOut->hide();
}

dose::~dose()
{
    delete ui;
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di collegarsi al dispositivo mediante rete wifi

void dose::on_pbNetConnect_released()
{
    ui->gbUSBCom->setEnabled(false);
}

//------------------------------------------------------------------------------------------

//Se viene modificata la com al checkbox mi disconnetto

void dose::on_pbPortName_editTextChanged(const QString &arg1)
{
    QString arg = arg1;
    ui->led->turnOff();
}

//------------------------------------------------------------------------------------------

//Gestione invio dati su USB

void dose::on_pbDose_released()
{
    Syncronize->stop();
    //avvio un timer di 250ms che mi richiama la funzione sottostante che inizia la scrittura delle schedulazioni orarie
    //Uso un timer per evitare la condizione pwer la quale premo questo tasto nell'esatto istante in cui il dispositivo sta inviando la sincronizzazione, e quindi ottengo un afalsa partenza
    QTimer::singleShot(500, this, SLOT(dosing()));
}

void dose::dosing()
{
    QJsonObject jsonObject;
    jsonObject.insert("CMD", 1);
    jsonObject.insert("PUMP", ui->cbnpump->currentIndex());
    jsonObject.insert("QUANTITY", ui->leQuantity->text().toFloat());
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    Syncronize->start();
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_pbBreak_released()
{
    Syncronize->stop();
    //avvio un timer di 250ms che mi richiama la funzione sottostante che inizia la scrittura delle schedulazioni orarie
    //Uso un timer per evitare la condizione pwer la quale premo questo tasto nell'esatto istante in cui il dispositivo sta inviando la sincronizzazione, e quindi ottengo un afalsa partenza
    QTimer::singleShot(500, this, SLOT(stopDosing()));

    QJsonObject jsonObject;
    jsonObject.insert("CMD", 7);
    jsonObject.insert("PUMP", ui->cbnpump->currentIndex());
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
}

void dose::stopDosing()
{
    QJsonObject jsonObject;
    jsonObject.insert("CMD", 7);
    jsonObject.insert("PUMP", ui->cbnpump->currentIndex());
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    Syncronize->start();
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_cbnpump_currentIndexChanged(int index)
{

    QSqlQuery query;
    query.prepare("SELECT fact_calibration FROM settings WHERE id_pump = ?");
    query.bindValue(0, index);
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    double out = 0;
    while (query.next())
    {
        out = query.value(0).toDouble();
        ui->dscalibrate->setValue(out);
    }
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_dscalibrate_valueChanged(double arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE settings set fact_calibration = ? WHERE id_pump IS ?");
    query.bindValue(0, ui->dscalibrate->value());
    query.bindValue(1, ui->cbnpump->currentIndex());
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    SyncLineElement(3);
//    SendConfiguration = 1;
}

void dose::UpdateLine()
{
    int pump = 0;
    QSqlQuery query;
    query.prepare("SELECT description, abilitation, capacity, timer_abilitation, level FROM line");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    pump = 0;
    while (query.next())
    {
        QString out = query.value(0).toString();
        if(pump == 0)
            ui->leSolDesc_2->setText(out);
        if(pump == 1)
            ui->leSolDesc_3->setText(out);
        if(pump == 2)
            ui->leSolDesc_4->setText(out);
        if(pump == 3)
            ui->leSolDesc_5->setText(out);
        //carico valori in db per quanto riguarda la descrizione della linea
        out = query.value(1).toString();
        bool status = false;
        if(out.toInt() != 0)status = true;
        if(pump == 0)
            ui->cbAbleSol_2->setChecked(status);
        if(pump == 1)
            ui->cbAbleSol_3->setChecked(status);
        if(pump == 2)
            ui->cbAbleSol_4->setChecked(status);
        if(pump == 3)
            ui->cbAbleSol_5->setChecked(status);
        //carico valori  in db per quanto riguarda la capacità del serbatoio
        float getFlow = query.value(2).toFloat();
        int actLevel = query.value(4).toInt();
        if(pump == 0)
        {
            ui->leCapacitySol_2->clear();
            ui->leCapacitySol_2->setText(QString::number(getFlow));
            ui->lResidualSol_2->setText(QString::number((actLevel*getFlow)/100));
        }
        if(pump == 1)
        {
            ui->leCapacitySol_3->clear();
            ui->leCapacitySol_3->setText(QString::number(getFlow));
            ui->lResidualSol_3->setText(QString::number((actLevel*getFlow)/100));
        }
        if(pump == 2)
        {
            ui->leCapacitySol_4->clear();
            ui->leCapacitySol_4->setText(QString::number(getFlow));
            ui->lResidualSol_4->setText(QString::number((actLevel*getFlow)/100));
        }
        if(pump == 3)
        {
            ui->leCapacitySol_5->clear();
            ui->leCapacitySol_5->setText(QString::number(getFlow));
            ui->lResidualSol_5->setText(QString::number((actLevel*getFlow)/100));
        }
        //carico valori  in db per quanto riguarda l'abilitazione del controllo timerizzato
        bool timAble = query.value(3).toInt();
        if(pump == 0)
            ui->cbAbleTimeSol_2->setChecked(timAble);
        if(pump == 1)
            ui->cbAbleTimeSol_3->setChecked(timAble);
        if(pump == 2)
            ui->cbAbleTimeSol_4->setChecked(timAble);
        if(pump == 3)
            ui->cbAbleTimeSol_5->setChecked(timAble);

        if(pump == 0)
        {
            ui->cbAbleSol_2->setEnabled(false);
            ui->leCapacitySol_2->setEnabled(false);
            ui->pbRefilSol_2->setEnabled(false);
            ui->cbAbleTimeSol_2->setEnabled(false);
        }
        if(pump == 1)
        {
            ui->cbAbleSol_3->setEnabled(false);
            ui->leCapacitySol_3->setEnabled(false);
            ui->pbRefilSol_3->setEnabled(false);
            ui->cbAbleTimeSol_3->setEnabled(false);
        }
        if(pump == 2)
        {
            ui->cbAbleSol_4->setEnabled(false);
            ui->leCapacitySol_4->setEnabled(false);
            ui->pbRefilSol_4->setEnabled(false);
            ui->cbAbleTimeSol_4->setEnabled(false);
        }
        if(pump == 3)
        {
            ui->cbAbleSol_5->setEnabled(false);
            ui->leCapacitySol_5->setEnabled(false);
            ui->pbRefilSol_5->setEnabled(false);
            ui->cbAbleTimeSol_5->setEnabled(false);
        }

        if(pump == 0)
        {
            //            ui->pbResidualSol_2->setValue(actLevel);
            QObject *bar = tankLevelObject1->findChild<QObject*>("tank");
            if (bar)
                bar->setProperty("progress", actLevel);
            qDebug()<<bar->property("progress");
        }
        if(pump == 1)
        {
            //            ui->pbResidualSol_2->setValue(actLevel);
            QObject *bar = tankLevelObject2->findChild<QObject*>("tank");
            if (bar)
                bar->setProperty("progress", actLevel);
            qDebug()<<bar->property("progress");
        }
        if(pump == 2)
        {
            //            ui->pbResidualSol_2->setValue(actLevel);
            QObject *bar = tankLevelObject3->findChild<QObject*>("tank");
            if (bar)
                bar->setProperty("progress", actLevel);
            qDebug()<<actLevel;
            qDebug()<<bar->property("progress");
        }
        if(pump == 3)
        {
            //            ui->pbResidualSol_2->setValue(actLevel);
            QObject *bar = tankLevelObject4->findChild<QObject*>("tank");
            if (bar)
                bar->setProperty("progress", actLevel);
            qDebug()<<bar->property("progress");
        }
        UpdateStime();
        pump++;

    }
}


void dose::processError(const QString &s)
{
    ui->led->turnOff();
    setControlsEnabled(true);
    ui->statusLabel->setText(tr("Status: Not running, %1.").arg(s));
}

void dose::processTimeout(const QString &s)
{
    setControlsEnabled(true);
    ui->statusLabel->setText(tr("Status: Running, %1.").arg(s));
}

void dose::setControlsEnabled(bool enable)
{
    ui->cbCom->setEnabled(enable);
    ui->tbStdOut->setEnabled(enable);

}

void dose::transaction()
{
    ui->led->turnOn();
    setControlsEnabled(false);
    ui->statusLabel->setText(tr("Status: Running, connected to port %1.")
                             .arg(ui->cbCom->currentText()));
}






uint32_t timetoremain = 0;
uint32_t totval = 0;
int rowIndex[7];
void dose::showResponse(const QString &s)
{
    //Split in a list all json's frame
    QList<QString> preparser;
    preparser=s.split('{}');
    for(int i=0; i<preparser.size(); i++)
    {
    //ui->tbStdOut->append(s);
    //Ricevo dati da USB, li converto in string e li mostro nel txt box
    setControlsEnabled(true);
    ui->led->turnOn();
    //QJsonDocument jsonResponse = QJsonDocument::fromJson(s.toUtf8());
    QJsonDocument jsonResponse = QJsonDocument::fromJson(preparser.at(i).toUtf8());

    QJsonDocument doc(jsonResponse);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    ui->tbStdOut->append("doDoser: "+strJson);

    int y = 0;
    if(jsonResponse.isEmpty())
    {
        jsonParserErrorCounter++;
        ui->tbStdOut->append(QTime::currentTime().toString()+" --- JsonParsingError: "+QString::number(jsonParserErrorCounter)+s);
    }
    QJsonObject jsonObject = jsonResponse.object();
    if(jsonObject.size() > 1)
    {
        if(jsonObject["CMD"].toInt() == 8)
        {
            //ho ricevuto un errore :
            //Verifico che data contenga effettivamente i dati che vado a richiedere
            if(jsonObject["error-type"].toInt() == ERROR_LINE_NOT_ABLE)
            {
                QMessageBox::critical(this,  tr(TITLE_APP),
                                      tr("Impossibile eseguire l'erogazioe\nla liea è disabilitata\nClick Close per uscire."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: impossible to dose, the line is disabled");
            }
            if(jsonObject["error-type"].toInt() == ERROR_NO_PUMP_ASSOCIATED)
            {
                QMessageBox::critical(this, tr(TITLE_APP),
                                      tr("Impossibile eseguire l'erogazione\nnon ci sono pompe associate alla linea\nClick Close per uscire."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: impossible to dose, the line don't have a pump associated");
            }
            if(jsonObject["error-type"].toInt() == ERROR_PUMP_ALREADY_STOPED)
            {
                QMessageBox::critical(this, tr(TITLE_APP),
                                      tr("Impossibile iterrompere la linea in quanto già ferma\nVerificare di aver selezionato la linea corretta\nClick Close per uscire."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: impossible to stop dose, the line is already stopped");
            }
            if(jsonObject["error-type"].toInt() == ERROR_LINE_NOT_FREE)
            {
                QMessageBox::critical(this, tr(TITLE_APP),
                                      tr("Si prega di attendere la fine dell'attuale erogazione."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: impossible to dose, the line is already in dosing time");
            }
            if(jsonObject["error-type"].toInt() == ERROR_NO_RTC_COM)
            {
                QMessageBox::critical(this, tr(TITLE_APP),
                                      tr("Attenzione!, orario di sistema errato, reimpostare data e ora."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: system time wrong");
            }
            if(jsonObject["error-type"].toInt() == ERROR_NO_CALIB_VALUE)
            {
                QMessageBox::critical(this, tr(TITLE_APP),
                                      tr("Attenzione!, coefficiente di taratura nullo, inpossibile erogare."),
                                      QMessageBox::Close);
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Error: wrong line calibration value");
            }
        }
        if(jsonObject["CMD"].toInt() == 10)
        {
            int y = 0;
            QString actValue;
            for(y = 0; y < 143; y++)//solo la prima parte del messaggio contiene la configurazione, la restante la devo aggiornare sempre
                actValue.append(s[y]);
            //Verifico se ci sono cambiamenti da visualizzare e salvare:

            //int diff = QString::compare(preValue, actValue, Qt::CaseInsensitive);
           int diff=1;
            if(diff != 0)
            {
                //Se ci sono differenze con i valori precedenti aggiorno dbe interfaccia
                ReadLineStatus = 0;
            }
            if(ReadLineStatus == 0)
            {//se è un messaggio di risincronizzazione device->pc
                QJsonArray linesLevelsArray = jsonObject["levels"].toArray();
                QJsonArray linesCapacityArray = jsonObject["capacity"].toArray();
                QJsonArray linesAbleArray = jsonObject["able"].toArray();
                QJsonArray linesAbleTimerArray = jsonObject["timer-able"].toArray();
                QJsonArray linesCalibrationArray = jsonObject["calibration"].toArray();
                int i = 0;
                for(i = 0; i < linesLevelsArray.size(); i++)
                {
                    QSqlQuery query;
                    query.prepare("UPDATE line SET level = ?, capacity = ?, abilitation = ?, timer_abilitation = ? WHERE id IS ?");
                    query.bindValue(0, linesLevelsArray[i].toDouble());
                    query.bindValue(1, linesCapacityArray[i].toDouble());
                    query.bindValue(2, linesAbleArray[i].toInt());
                    query.bindValue(3, linesAbleTimerArray[i].toInt());
                    query.bindValue(4, i);
                    query.exec();
                    if(query.lastError().isValid())
                        qDebug()<<query.lastError();
                    query.prepare("UPDATE settings SET fact_calibration = ? WHERE id_pump IS ?");
                    query.bindValue(0, linesCalibrationArray[i].toInt());
                    query.bindValue(1, i);
                    query.exec();
                    if(query.lastError().isValid())
                        qDebug()<<query.lastError();
                }
                ReadLineStatus = 1;
                UpdateLine();
                preValue = actValue;
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Sync line status & configuration successfully");
            }
            QJsonArray timestamp = jsonObject["timestamp"].toArray();
            QString stime(QString::number(timestamp[0].toInt()));
            stime.append("/");
            stime.append(QString::number(timestamp[1].toInt()));
            stime.append("/");
            stime.append(QString::number(timestamp[2].toInt()));
            stime.append(" ");
            stime.append(QString::number(timestamp[3].toInt()));
            stime.append(":");
            stime.append(QString::number(timestamp[4].toInt()));
            stime.append(":");
            stime.append(QString::number(timestamp[5].toInt()));
            stime.append(" dow: ");
            stime.append(QString::number(timestamp[6].toInt()));
            ui->lTime->setText(stime);
            //********************************************************
            QJsonArray lineleds = jsonObject["pump-active"].toArray();
            ui->led_line_1->turnOn(lineleds[0].toInt());
            ui->led_line_2->turnOn(lineleds[1].toInt());
            ui->led_line_3->turnOn(lineleds[2].toInt());
            ui->led_line_4->turnOn(lineleds[3].toInt());
            ui->led_line_5->turnOn(lineleds[4].toInt());
            ui->led_line_6->turnOn(lineleds[5].toInt());
            ui->led_line_7->turnOn(lineleds[6].toInt());
            ui->led_line_8->turnOn(lineleds[7].toInt());
            //Aggiornamento stato dosaggio
            //********************************************************
            if(timetoremain < jsonObject["doseT"].toInt())//se il valore precedente del tempo restante di dosaggio è minore di quello attuale allora ho un nuovo dosaggio
            {
                //inizio dosaggio in corso
                ui->statusBar->showMessage("Dosing...");
                timetoremain = jsonObject["doseT"].toInt();
                ui->pbDosing->show();
                ui->pbDosing->setMinimum(0);
                ui->pbDosing->setMaximum(100);
                //ui->pbDosing->setValue(0);
                totval = timetoremain;
                QString pumpStatus;
                for(int y=0; y < 8; y++)
                    pumpStatus.append(QString::number(lineleds[y].toInt()));
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Start dosing"\
                                     +pumpStatus);
            }
            //********************************************************
            //ui->pbDosing->reset();
            int Ttor = jsonObject["doseT"].toInt();
            timetoremain = Ttor;
            if(timetoremain == 0)
            {
                ui->statusBar->showMessage("Ready!");
                ui->pbDosing->hide();
                ui->pbDosing->setValue(0);
                totval = 0;
                // ui->tbStdOut->append(QTime::currentTime().toString()+" - End dosing");
            }
            else
            {
                ui->pbDosing->setValue(100-((timetoremain*100)/totval));
                ui->tbStdOut->append(QTime::currentTime().toString()+" - dosing..."+QString::number(100-((timetoremain*100)/totval))+"%");
                //               ui->tbStdOut->append(QTime::currentTime().toString()+" - update dosing Time:"+QString::number(timetoremain));
            }
            //Log printout
        }
        if(jsonObject["CMD"].toInt() == 9)
        {

            if(jsonObject["NOIC"] != send_counter)
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Fail write counters mismatch");

            if(send_counter < NUM_OF_SCHEDULER)
            {
                ui->pbDatamoving->show();
                timerDose_type SchedulerFrame;
                QJsonObject jsonObjectToSend;
                QSqlQuery query;
                query.prepare("SELECT id, time, id_line, quantity, dayOfWek, row FROM timerDose WHERE id = ?");
                query.bindValue(0, send_counter);
                query.exec();
                while (query.next())
                {
                    QString Hour = query.value(1).toString().mid(0, 2);
                    QString Min = query.value(1).toString().mid(3, 2);
                    int row = query.value(5).toInt();
                    SchedulerFrame.ID = query.value(0).toInt();
                    SchedulerFrame.ID_LINE = query.value(2).toInt();
                    SchedulerFrame.QUANTITY = query.value(3).toFloat();
                    SchedulerFrame.DAYOFWEEK = query.value(4).toInt();
                    SchedulerFrame.HOUR = Hour.toInt();
                    SchedulerFrame.MINUTE = Min.toInt();
                }
                jsonObjectToSend.insert("CMD", 9);
                jsonObjectToSend.insert("NOI", send_counter);
                jsonObjectToSend.insert("BACON",QJsonArray()<<SchedulerFrame.ID<<SchedulerFrame.HOUR<<SchedulerFrame.MINUTE<<SchedulerFrame.EXEC<<SchedulerFrame.ID_LINE<<SchedulerFrame.QUANTITY<<SchedulerFrame.DAYOFWEEK);
                QJsonDocument doc(jsonObjectToSend);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                thread.transaction(ui->cbCom->currentText(),
                                   USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                                   strJson);
                ui->pbDatamoving->setValue(send_counter);
                send_counter++;
                if(send_counter == NUM_OF_SCHEDULER)
                {
                    ui->pbDatamoving->hide();
                    //Corretta ricezione di tutta la configurazione oraria
                    QMessageBox::information(this, tr(TITLE_APP),
                                             tr("Configurazione oraria "
                                                " inviata correttamente."));
                    Syncronize->start();
                    ui->tbStdOut->append(QTime::currentTime().toString()+" - Time and date configuration sent correctly");
                }
            }
        }
        if(jsonObject["CMD"].toInt() == 5)
        {
            if(jsonObject["NOIC"] != send_counter)
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Fail read counters mismatch");

            if(send_counter < NUM_OF_SCHEDULER)
            {
                int idOfItem = 0;

                int index;
                if(send_counter == 1)
                {
                    for(index =0; index < 7; index++)
                        rowIndex[index]=0;
                    ui->pbDatamoving->show();
                }
                QJsonArray dataArray = jsonObject["BACON"].toArray();
                QSqlQuery query;
                idOfItem = index;
                //terza fase inserisco l'item nel db
                query.prepare("UPDATE timerDose set time = ?, id_line = ?, quantity = ?, dayOfWek = ?, row = ? WHERE id IS ?");
                QTime timeSupport(dataArray[1].toInt(), dataArray[2].toInt());

                query.bindValue(0, timeSupport);
                query.bindValue(1, dataArray[4].toInt());
                query.bindValue(2, dataArray[5].toInt());
                query.bindValue(3, dataArray[6].toInt());
                if(dataArray[5].toInt() != NULL)
                { //se presente una quantità valida allora in row segno l'indice corretto in funzione del giorno della settimana
                    query.bindValue(4, rowIndex[dataArray[6].toInt()]);
                    rowIndex[dataArray[6].toInt()]++;
                }else
                {//altrimenti metto il valor nullo 255 che nel mio sistema indica che non ci sono programmazioni
                    query.bindValue(4, 255);//altrimenti è 255
                }
                query.bindValue(5, dataArray[0].toInt());
                query.exec();
                if(query.lastError().isValid())
                    qDebug()<<query.lastError();
                QJsonObject jsonObjectToSend;
                jsonObjectToSend.insert("CMD", 5);
                jsonObjectToSend.insert("NOI", send_counter);
                QJsonDocument doc(jsonObjectToSend);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                thread.transaction(ui->cbCom->currentText(),
                                   USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                                   strJson);
                send_counter++;
                ui->pbDatamoving->setValue(send_counter);
            }
            else
            {
                ui->pbDatamoving->hide();
                updateTable();
                updateDoseSummary();
                //Corretta ricezione di tutta laconfigurazione oraria
                QMessageBox::information(this, tr(TITLE_APP),
                                         tr("Configurazione oraria "
                                            " ricevuta correttamente."));
                Syncronize->start();
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Time and date configuration received correctly");
                send_counter = 0;
            }
        }
        if(jsonObject["CMD"].toInt() == 6)
        {
            //Ho ricevuto una conferma di termine o conferma comando
            if(jsonObject["TYPE"] == 0)
            {
                //Corretta impostazione oraria
                QMessageBox::information(this, tr(TITLE_APP),
                                         tr("Data e ora impostate "
                                            "correttamente."));
                ui->tbStdOut->append(QTime::currentTime().toString()+" - Time and date set correctly");
            }
        }
        if(jsonObject["CMD"].toInt() == 12)
        {

        }
    }
    else
    {//è arrivato un solo oggetto json
        if(jsonObject["CMD"].toInt() == 3)
        {
            ui->tbStdOut->append(QTime::currentTime().toString()+" - Read status lines from device");
        }
        if(jsonObject["CMD"].toInt() == 4)
        {
            ui->tbStdOut->append(QTime::currentTime().toString()+" - Reset liquid level");
        }
        if(jsonObject["CMD"].toInt() == 11)
        {
            ui->tbStdOut->append(QTime::currentTime().toString()+" - Set New line configuration");
        }
    }

    }
}
void dose::on_pbRefresh_released()
{
    ui->cbCom->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->cbCom->addItem(info.portName());
}

void dose::on_pbStdOut_released()
{
    ui->tbStdOut->clear();
}

void dose::on_pushButton_released()
{
    if(ui->cbAbleSol_2->isEnabled())
    {
       // Sync();
        ui->twMenu->widget(0)->setEnabled(true);
        ui->twMenu->widget(1)->setEnabled(true);
        ui->twMenu->widget(2)->setEnabled(true);
        Syncronize->start();
        ui->cbAbleSol_2->setEnabled(false);
        ui->cbAbleTimeSol_2->setEnabled(false);
        ui->leCapacitySol_2->setEnabled(false);
        ui->pbRefilSol_2->setEnabled(false);
        //        ui->pbResidualSol_2->setEnabled(false);
        //we color in grey tank
        QObject *bar;
        bar = tankLevelObject1->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_2->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }
        qDebug()<<"Point B";

        ui->cbAbleSol_3->setEnabled(false);
        ui->cbAbleTimeSol_3->setEnabled(false);
        ui->leCapacitySol_3->setEnabled(false);
        ui->pbRefilSol_3->setEnabled(false);
        //ui->pbResidualSol_3->setEnabled(false);
        //we color in grey tank
        bar = tankLevelObject2->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_3->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }


        ui->cbAbleSol_4->setEnabled(false);
        ui->cbAbleTimeSol_4->setEnabled(false);
        ui->leCapacitySol_4->setEnabled(false);
        ui->pbRefilSol_4->setEnabled(false);
        // ui->pbResidualSol_4->setEnabled(false);
        //we color in grey tank
        bar = tankLevelObject3->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_4->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }
        ui->cbAbleSol_5->setEnabled(false);
        ui->cbAbleTimeSol_5->setEnabled(false);
        ui->leCapacitySol_5->setEnabled(false);
        ui->pbRefilSol_5->setEnabled(false);
        // ui->pbResidualSol_5->setEnabled(false);
        //we color in grey tank

        bar = tankLevelObject4->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_5->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }

        ui->cbAbleSol_6->setEnabled(false);
        ui->cbAbleTimeSol_6->setEnabled(false);
        ui->leCapacitySol_6->setEnabled(false);
        ui->pbRefilSol_6->setEnabled(false);

        bar = tankLevelObject5->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_6->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }

        ui->cbAbleSol_7->setEnabled(false);
        ui->cbAbleTimeSol_7->setEnabled(false);
        ui->leCapacitySol_7->setEnabled(false);
        ui->pbRefilSol_7->setEnabled(false);
        bar = tankLevelObject6->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_7->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }
        ui->cbAbleSol_8->setEnabled(false);
        ui->cbAbleTimeSol_8->setEnabled(false);
        ui->leCapacitySol_8->setEnabled(false);
        ui->pbRefilSol_8->setEnabled(false);

        bar = tankLevelObject7->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_8->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }
        ui->cbAbleSol_9->setEnabled(false);
        ui->cbAbleTimeSol_9->setEnabled(false);
        ui->leCapacitySol_9->setEnabled(false);
        ui->pbRefilSol_9->setEnabled(false);
        bar = tankLevelObject8->findChild<QObject*>("tank");
        if (bar)
        {
            if(ui->cbAbleSol_9->isChecked())
            {
                bar->setProperty("enable", true);
            }
            else
            {
                bar->setProperty("enable", false);
            }
        }
         SyncLineElement(0);
    }
    else
    {

       // SendConfiguration = 1;
        ui->twMenu->widget(0)->setEnabled(false);
        ui->twMenu->widget(1)->setEnabled(false);
        ui->twMenu->widget(2)->setEnabled(false);
        Syncronize->stop();
        ui->cbAbleSol_2->setEnabled(true);
        ui->cbAbleTimeSol_2->setEnabled(true);
        ui->leCapacitySol_2->setEnabled(true);
        ui->pbRefilSol_2->setEnabled(true);
        //        ui->pbResidualSol_2->setEnabled(true);
        QObject *bar;

            bar = tankLevelObject1->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_2->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
            qDebug()<<"Point C";

        ui->cbAbleSol_3->setEnabled(true);
        ui->cbAbleTimeSol_3->setEnabled(true);
        ui->leCapacitySol_3->setEnabled(true);
        ui->pbRefilSol_3->setEnabled(true);
        //ui->pbResidualSol_3->setEnabled(true);
        //we color in grey tank

            bar = tankLevelObject2->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_3->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_4->setEnabled(true);
        ui->cbAbleTimeSol_4->setEnabled(true);
        ui->leCapacitySol_4->setEnabled(true);
        ui->pbRefilSol_4->setEnabled(true);
        //ui->pbResidualSol_4->setEnabled(true);
        //we color in grey tank

            bar = tankLevelObject3->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_4->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_5->setEnabled(true);
        ui->cbAbleTimeSol_5->setEnabled(true);
        ui->leCapacitySol_5->setEnabled(true);
        ui->pbRefilSol_5->setEnabled(true);
        // ui->pbResidualSol_5->setEnabled(true);
        //we color in grey tank

            bar = tankLevelObject4->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_5->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_6->setEnabled(true);
        ui->cbAbleTimeSol_6->setEnabled(true);
        ui->leCapacitySol_6->setEnabled(true);
        ui->pbRefilSol_6->setEnabled(true);

            bar = tankLevelObject5->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_6->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_7->setEnabled(true);
        ui->cbAbleTimeSol_7->setEnabled(true);
        ui->leCapacitySol_7->setEnabled(true);
        ui->pbRefilSol_7->setEnabled(true);

            bar = tankLevelObject6->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_7->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_8->setEnabled(true);
        ui->cbAbleTimeSol_8->setEnabled(true);
        ui->leCapacitySol_8->setEnabled(true);
        ui->pbRefilSol_8->setEnabled(true);

            bar = tankLevelObject7->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_8->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
        ui->cbAbleSol_9->setEnabled(true);
        ui->cbAbleTimeSol_9->setEnabled(true);
        ui->leCapacitySol_9->setEnabled(true);
        ui->pbRefilSol_9->setEnabled(true);

            bar = tankLevelObject8->findChild<QObject*>("tank");
            if (bar)
            {
                if(ui->cbAbleSol_9->isChecked())
                {
                    bar->setProperty("enable", true);
                }
                else
                {
                    bar->setProperty("enable", false);
                }
            }
    }
}

void dose::on_twMenu_currentChanged(int index)
{
    QSqlQuery query;
    //dosaggio manuale
    if(index == 1)
    {//popolo con il nome delle soluzioni il selettore di linea
        QSqlQuery _query;
        _query.prepare("SELECT description FROM line ORDER BY id ASC");
        _query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();

        int count = 0;
        while (_query.next())
        {
            if(count == 0)
            {
                ui->cbnpump->setItemText(count, _query.value(0).toString());
            }
            if(count == 1)
            {
                ui->cbnpump->setItemText(count, _query.value(0).toString());
            }
            if(count == 2)
            {
                ui->cbnpump->setItemText(count, _query.value(0).toString());
            }
            if(count == 3)
            {
                ui->cbnpump->setItemText(count, _query.value(0).toString());
            }
            count++;
        }
    }
    if(index == 2)
    {
        updateDoseSummary();
        updateTable();
    }
    //timer
    if(index == 3)
    {
        ReadLineStatus = 0;
        UpdateStime();
    }
}

void dose::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->tbStdOut->show();
        ui->statusLabel->show();
        ui->pbStdOut->show();
    }
    else
    {
        ui->tbStdOut->hide();
        ui->statusLabel->hide();
        ui->pbStdOut->hide();
    }
}

void dose::on_cbLineSlave_toggled(bool checked)
{
    if(checked)
    {
        ui->twMenu->addTab(widgetSlave,"Gestione linee Slave");
        ui->lline5_1->show();
        ui->llvalue5_1->show();
        ui->lline5_2->show();
        ui->llvalue5_2->show();
        ui->lline5_3->show();
        ui->llvalue5_3->show();
        ui->lline5_4->show();
        ui->llvalue5_4->show();
        ui->lline5_5->show();
        ui->llvalue5_5->show();
        ui->lline5_6->show();
        ui->llvalue5_6->show();
        ui->lline5_7->show();
        ui->llvalue5_7->show();

        ui->lline6_1->show();
        ui->llvalue6_1->show();
        ui->lline6_2->show();
        ui->llvalue6_2->show();
        ui->lline6_3->show();
        ui->llvalue6_3->show();
        ui->lline6_4->show();
        ui->llvalue6_4->show();
        ui->lline6_5->show();
        ui->llvalue6_5->show();
        ui->lline6_6->show();
        ui->llvalue6_6->show();
        ui->lline6_7->show();
        ui->llvalue6_7->show();

        ui->lline7_1->show();
        ui->llvalue7_1->show();
        ui->lline7_2->show();
        ui->llvalue7_2->show();
        ui->lline7_3->show();
        ui->llvalue7_3->show();
        ui->lline7_4->show();
        ui->llvalue7_4->show();
        ui->lline7_5->show();
        ui->llvalue7_5->show();
        ui->lline7_6->show();
        ui->llvalue7_6->show();
        ui->lline7_7->show();
        ui->llvalue7_7->show();

        ui->lline8_1->show();
        ui->llvalue8_1->show();
        ui->lline8_2->show();
        ui->llvalue8_2->show();
        ui->lline8_3->show();
        ui->llvalue8_3->show();
        ui->lline8_4->show();
        ui->llvalue8_4->show();
        ui->lline8_5->show();
        ui->llvalue8_5->show();
        ui->lline8_6->show();
        ui->llvalue8_6->show();
        ui->lline8_7->show();
        ui->llvalue8_7->show();
    }
    else
    {
        ui->twMenu->removeTab(4);
        ui->lline5_1->hide();
        ui->llvalue5_1->hide();
        ui->lline5_2->hide();
        ui->llvalue5_2->hide();
        ui->lline5_3->hide();
        ui->llvalue5_3->hide();
        ui->lline5_4->hide();
        ui->llvalue5_4->hide();
        ui->lline5_5->hide();
        ui->llvalue5_5->hide();
        ui->lline5_6->hide();
        ui->llvalue5_6->hide();
        ui->lline5_7->hide();
        ui->llvalue5_7->hide();

        ui->lline6_1->hide();
        ui->llvalue6_1->hide();
        ui->lline6_2->hide();
        ui->llvalue6_2->hide();
        ui->lline6_3->hide();
        ui->llvalue6_3->hide();
        ui->lline6_4->hide();
        ui->llvalue6_4->hide();
        ui->lline6_5->hide();
        ui->llvalue6_5->hide();
        ui->lline6_6->hide();
        ui->llvalue6_6->hide();
        ui->lline6_7->hide();
        ui->llvalue6_7->hide();

        ui->lline7_1->hide();
        ui->llvalue7_1->hide();
        ui->lline7_2->hide();
        ui->llvalue7_2->hide();
        ui->lline7_3->hide();
        ui->llvalue7_3->hide();
        ui->lline7_4->hide();
        ui->llvalue7_4->hide();
        ui->lline7_5->hide();
        ui->llvalue7_5->hide();
        ui->lline7_6->hide();
        ui->llvalue7_6->hide();
        ui->lline7_7->hide();
        ui->llvalue7_7->hide();

        ui->lline8_1->hide();
        ui->llvalue8_1->hide();
        ui->lline8_2->hide();
        ui->llvalue8_2->hide();
        ui->lline8_3->hide();
        ui->llvalue8_3->hide();
        ui->lline8_4->hide();
        ui->llvalue8_4->hide();
        ui->lline8_5->hide();
        ui->llvalue8_5->hide();
        ui->lline8_6->hide();
        ui->llvalue8_6->hide();
        ui->lline8_7->hide();
        ui->llvalue8_7->hide();
    }
}

void dose::on_twMenu_tabBarClicked(int index)
{
    //inposto la data e ora corrente nei campi per settare la data e ora nuovi
    if (index == 0)
    {
        QDate currDate;
        QTime currTime;
        currDate = QDate::currentDate();
        currTime = QTime::currentTime();
        ui->dateTimeEdit->setDate(currDate);
        ui->dateTimeEdit->setTime(currTime);
    }
}

void dose::on_pbSendNetCfg_released()
{
    QJsonObject jsonObjectToSend;
    jsonObjectToSend.insert("CMD", 12);
    jsonObjectToSend.insert("IP", ui->leIP1->text());
    jsonObjectToSend.insert("PORT", ui->lePort1->text());
    jsonObjectToSend.insert("NET", ui->leNet1->text());
    jsonObjectToSend.insert("GAT", ui->leGate1->text());
    jsonObjectToSend.insert("SSID", ui->leSSID->text());
    jsonObjectToSend.insert("PWD", ui->lePWD_WIFI->text());
    jsonObjectToSend.insert("DHCP", ui->cbDHCP->checkState());
    QJsonDocument doc(jsonObjectToSend);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
}


