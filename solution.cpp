#include "dose.h"
#include "ui_dose.h"
#include "hled.h"
#include "qmessagebox.h"
#include "stdint-gcc.h"


//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_pbRefilSol_2_released()
{
    QJsonObject jsonObject;
    jsonObject.insert("CMD",4);
    jsonObject.insert("PUMP",0);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    QObject *bar = tankLevelObject1->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("progress", 100);
    qDebug()<<bar->property("progress");
    //ui->pbResidualSol_2->setValue(100);
    //    SendConfiguration = 1;
}
void dose::on_pbRefilSol_3_released()
{
    QJsonObject jsonObject;
    jsonObject.insert("CMD",4);
    jsonObject.insert("PUMP",1);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);

    QObject *bar = tankLevelObject2->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("progress", 100);
    qDebug()<<bar->property("progress");
    //    SendConfiguration = 1;
}
void dose::on_pbRefilSol_4_released()
{
    QJsonObject jsonObject;
    jsonObject.insert("CMD",4);
    jsonObject.insert("PUMP",2);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);

    QObject *bar = tankLevelObject3->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("progress", 100);
    qDebug()<<bar->property("progress");
    //    SendConfiguration = 1;
}
void dose::on_pbRefilSol_5_released()
{

    QJsonObject jsonObject;
    jsonObject.insert("CMD",4);
    jsonObject.insert("PUMP",3);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);

    QObject *bar = tankLevelObject4->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("progress", 100);
    qDebug()<<bar->property("progress");
    //    SendConfiguration = 1;
}

//------------------------------------------------------------------------------------------

//
QString strJson;
void dose::SyncLineElement(int element)
{
    QSqlQuery query;
    QJsonObject jsonObject;

    float capacity[NUM_OF_PUMP];
    int abilitation[NUM_OF_PUMP];
    int timer_abilitation[NUM_OF_PUMP];
    int calibration[NUM_OF_LINE];
    int index = 0;

    //jsonObject.insert("CMD",11);


    query.prepare("SELECT fact_calibration, id_pump FROM settings ORDER BY id_pump ASC");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    int pump = 0;
    while (query.next())
    {
        pump = query.value(1).toInt();
        if(pump < NUM_OF_LINE)
            calibration[pump] = query.value(0).toInt();

    }
    index = 0;
    query.prepare("SELECT capacity, id, abilitation, timer_abilitation FROM line ORDER BY id ASC");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    while (query.next())
    {
        //carico valori  in db per quanto riguarda la capacità del serbatoio
        capacity[index] = query.value(0).toFloat();
        abilitation[index] = query.value(2).toInt();
        timer_abilitation[index] = query.value(3).toInt();
        if(index < NUM_OF_LINE)
            index++;
        else
            break;
    }
    index = 0;

    switch(element)
    {
    case 0:
         jsonObject.insert("CMD",17);
        jsonObject.insert("capacity",QJsonArray()<<capacity[0]<<capacity[1]<<capacity[2]<<capacity[3]);
        break;
    case 1:
         jsonObject.insert("CMD",14);
        jsonObject.insert("abilitation",QJsonArray()<<abilitation[0]<<abilitation[1]<<abilitation[2]<<abilitation[3]);
        break;
    case 2:
         jsonObject.insert("CMD",15);
        jsonObject.insert("timer-abilitation",QJsonArray()<<timer_abilitation[0]<<timer_abilitation[1]<<timer_abilitation[2]<<timer_abilitation[3]);
        break;
    case 3:
         jsonObject.insert("CMD",16);
        jsonObject.insert("calibration",QJsonArray()<<calibration[0]<<calibration[1]<<calibration[2]<<calibration[3]);
        break;
    }
    QJsonDocument doc(jsonObject);
    strJson=doc.toJson(QJsonDocument::Compact);
    ui->tbStdOut->append(strJson);
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    //Questo consente il refresh immadiato dello stato delle linee dopo la modifica, infatti la parte iniziale del pacchetto viene elaborata solo se differente dalla precedente!
    preValue.clear();
}


//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::Sync()
{
   // QSqlQuery query;
    QJsonObject jsonObject;
   /*
    float capacity[NUM_OF_PUMP];
    int abilitation[NUM_OF_PUMP];
    int timer_abilitation[NUM_OF_PUMP];
    int calibration[NUM_OF_LINE];
    int index = 0;
    if(SendConfiguration == 1)
    {

        jsonObject.insert("CMD",11);
        query.prepare("SELECT fact_calibration, id_pump FROM settings ORDER BY id_pump ASC");
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();

        int pump = 0;
        while (query.next())
        {
            pump = query.value(1).toInt();
            if(pump < NUM_OF_LINE)
                calibration[pump] = query.value(0).toInt();

        }
        index = 0;
        query.prepare("SELECT capacity, id, abilitation, timer_abilitation FROM line ORDER BY id ASC");
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();

        while (query.next())
        {
            //carico valori  in db per quanto riguarda la capacità del serbatoio
            capacity[index] = query.value(0).toFloat();
            abilitation[index] = query.value(2).toInt();
            timer_abilitation[index] = query.value(3).toInt();
            if(index < NUM_OF_LINE)
                index++;
            else
                break;
        }
        index = 0;

        jsonObject.insert("capacity",QJsonArray()<<capacity[0]<<capacity[1]<<capacity[2]<<capacity[3]);
        jsonObject.insert("abilitation",QJsonArray()<<abilitation[0]<<abilitation[1]<<abilitation[2]<<abilitation[3]);
        jsonObject.insert("timer-abilitation",QJsonArray()<<timer_abilitation[0]<<timer_abilitation[1]<<timer_abilitation[2]<<timer_abilitation[3]);
        jsonObject.insert("calibration",QJsonArray()<<calibration[0]<<calibration[1]<<calibration[2]<<calibration[3]);

          SendConfiguration = 0;
        QJsonDocument doc(jsonObject);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        ui->tbStdOut->append(strJson);
        thread.transaction(ui->cbCom->currentText(),
                           USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                           strJson);
        //Questo consente il refresh immadiato dello stato delle linee dopo la modifica, infatti la parte iniziale del pacchetto viene elaborata solo se differente dalla precedente!
        preValue.clear();
    }
    else
    {*/
        jsonObject.insert("CMD",10);
        QJsonDocument doc(jsonObject);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        ui->tbStdOut->append(strJson);
        thread.transaction(ui->cbCom->currentText(),
                           USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                           strJson);
 //   }


}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_leCapacitySol_2_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET capacity = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    //    query.bindValue(1, 100);
    query.bindValue(1, "0");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    qDebug()<<arg1;
    UpdateStime();

    //    SendConfiguration = 1;
}
void dose::on_leCapacitySol_3_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET capacity = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    //    query.bindValue(1, 100);
    query.bindValue(1, "1");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    UpdateStime();
    //    SendConfiguration = 1;
}
void dose::on_leCapacitySol_4_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET capacity = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    //    query.bindValue(1, 100);
    query.bindValue(1, "2");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    UpdateStime();
    //    SendConfiguration = 1;
}
void dose::on_leCapacitySol_5_textChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET capacity = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    //    query.bindValue(1, 100);
    query.bindValue(1, "3");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

    UpdateStime();
    //    SendConfiguration = 1;
}
void dose::on_leSolDesc_2_textEdited(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET description = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "0");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

}
void dose::on_leSolDesc_3_textEdited(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET description = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "1");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

}
void dose::on_leSolDesc_4_textEdited(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET description = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "2");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

}
void dose::on_leSolDesc_5_textEdited(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET description = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "3");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();

}
void dose::on_cbAbleSol_2_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "0");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(1);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleSol_3_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "1");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(1);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleSol_4_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "2");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(1);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleSol_5_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "3");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(1);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleTimeSol_2_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET timer_abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "0");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(2);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleTimeSol_3_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET timer_abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "1");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(2);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleTimeSol_4_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET timer_abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "2");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(2);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleTimeSol_5_stateChanged(int arg1)
{
    QSqlQuery query;
    query.prepare("UPDATE line SET timer_abilitation = ? WHERE id IS ?");
    query.bindValue(0, arg1);
    query.bindValue(1, "3");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
SyncLineElement(2);
    //    SendConfiguration = 1;
}
void dose::on_cbAbleSol_2_toggled(bool checked)
{
    ui->cbAbleTimeSol_2->setEnabled(checked);
    ui->leCapacitySol_2->setEnabled(checked);
    ui->pbRefilSol_2->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject1->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
    qDebug()<<"Point E";
    //    ui->pbResidualSol_2->setEnabled(checked);
}
void dose::on_cbAbleSol_3_toggled(bool checked)
{
    ui->cbAbleTimeSol_3->setEnabled(checked);
    ui->leCapacitySol_3->setEnabled(checked);
    ui->pbRefilSol_3->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject2->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
    //ui->pbResidualSol_3->setEnabled(checked);
}
void dose::on_cbAbleSol_4_toggled(bool checked)
{
    ui->cbAbleTimeSol_4->setEnabled(checked);
    ui->leCapacitySol_4->setEnabled(checked);
    ui->pbRefilSol_4->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject3->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
    //ui->pbResidualSol_4->setEnabled(checked);
}
void dose::on_cbAbleSol_5_toggled(bool checked)
{
    ui->cbAbleTimeSol_5->setEnabled(checked);
    ui->leCapacitySol_5->setEnabled(checked);
    ui->pbRefilSol_5->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject4->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
    //ui->pbResidualSol_5->setEnabled(checked);
}
void dose::on_cbAbleSol_6_toggled(bool checked)
{
    ui->cbAbleTimeSol_6->setEnabled(checked);
    ui->leCapacitySol_6->setEnabled(checked);
    ui->pbRefilSol_6->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject5->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
}
void dose::on_cbAbleSol_7_toggled(bool checked)
{
    ui->cbAbleTimeSol_7->setEnabled(checked);
    ui->leCapacitySol_7->setEnabled(checked);
    ui->pbRefilSol_7->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject6->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
}
void dose::on_cbAbleSol_8_toggled(bool checked)
{
    ui->cbAbleTimeSol_8->setEnabled(checked);
    ui->leCapacitySol_8->setEnabled(checked);
    ui->pbRefilSol_8->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject7->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
}
void dose::on_cbAbleSol_9_toggled(bool checked)
{
    ui->cbAbleTimeSol_9->setEnabled(checked);
    ui->leCapacitySol_9->setEnabled(checked);
    ui->pbRefilSol_9->setEnabled(checked);
    //we color in grey tank
    QObject *bar = tankLevelObject8->findChild<QObject*>("tank");
    if (bar)
        bar->setProperty("enable", checked);
}

void dose::UpdateStime(void)
{
    QSqlQuery query;
    int line = 0;
    int dow = 0;
    float weekMedia = 0;
    int remainWeek = 0;
    float qty = 0;
    for(line = 0; line < NUM_OF_LINE; line++)
    {
        weekMedia = 0;
        qty = 0;
        for(dow = 1; dow < 8; dow++)
        {
            query.prepare("SELECT TOTAL(quantity), level FROM timerDose, line  where timerDose.id_line == ?  AND line.id == ? AND dayOfWek == ? ");
            query.bindValue(0, line);
            query.bindValue(1, line);
            query.bindValue(2, dow);
            query.exec();
            if(query.lastError().isValid())
                qDebug()<<query.lastError();

            while (query.next())
            {
                //carico valori  in db per quanto riguarda la capacità del serbatoio
                weekMedia = weekMedia + query.value(0).toFloat();

            }
        }

        query.prepare("SELECT  level, capacity FROM line  where line.id == ? ");
        query.bindValue(0, line);
        query.exec();
        if(query.lastError().isValid())
            qDebug()<<query.lastError();

        while (query.next())
        {
            float level = query.value(0).toFloat();
            qty = (level * query.value(1).toFloat())/100;
        }
        if(line == 0)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_2->setText(QString::number(weekMedia));
            ui->lLastWeek_1->setText(QString::number(remainWeek));
        }
        if(line == 1)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_3->setText(QString::number(weekMedia));
            ui->lLastWeek_2->setText(QString::number(remainWeek));
        }
        if(line == 2)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_4->setText(QString::number(weekMedia));
            ui->lLastWeek_3->setText(QString::number(remainWeek));
        }
        if(line == 3)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_5->setText(QString::number(weekMedia));
            ui->lLastWeek_4->setText(QString::number(remainWeek));
        }
        if(line == 4)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_6->setText(QString::number(weekMedia));
            ui->lLastWeek_5->setText(QString::number(remainWeek));
        }
        if(line == 5)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_7->setText(QString::number(weekMedia));
            ui->lLastWeek_6->setText(QString::number(remainWeek));
        }
        if(line == 6)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_8->setText(QString::number(weekMedia));
            ui->lLastWeek_7->setText(QString::number(remainWeek));
        }
        if(line == 7)
        {
            remainWeek = (qty) / weekMedia;
            if(remainWeek < 0)
                remainWeek = 0;
            ui->lWeekDoseSol_9->setText(QString::number(weekMedia));
            ui->lLastWeek_8->setText(QString::number(remainWeek));
        }
    }
}
