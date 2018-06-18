#include "dose.h"
#include "ui_dose.h"
#include "qmessagebox.h"


//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_pbSetTime_released()
{//Comando di settaggio data e ora: secondo il formato: #6|0|Y|M|D|h|m|s|dow|-\n\r
    QDate supportDate = ui->dateTimeEdit->date();
    QTime supportTime = ui->dateTimeEdit->time();
    QJsonObject jsonObject;
    jsonObject.insert("CMD",6);
    jsonObject.insert("Y",supportDate.year());
    jsonObject.insert("M",supportDate.month());
    jsonObject.insert("D",supportDate.day());
    jsonObject.insert("h",supportTime.hour());
    jsonObject.insert("m",supportTime.minute());
    jsonObject.insert("s",supportTime.second());
    jsonObject.insert("dw",supportDate.dayOfWeek());
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    /*QString mex = "#6|0|";
     if(supportDate.year()-2000 < 10)
         mex.append('0');
     mex.append(QString::number(supportDate.year()-2000));
     mex.append('|');
     if(supportDate.month() < 10)
         mex.append('0');
     mex.append(QString::number(supportDate.month()));
     mex.append('|');
     if(supportDate.day() < 10)
         mex.append('0');
     mex.append(QString::number(supportDate.day()));
     mex.append('|');
     if(supportTime.hour() < 10)
         mex.append('0');
     mex.append(QString::number(supportTime.hour()));
     mex.append('|');
     if(supportTime.minute() < 10)
         mex.append('0');
     mex.append(QString::number(supportTime.minute()));
     mex.append('|');
     if(supportTime.second() < 10)
         mex.append('0');
     mex.append(QString::number(supportTime.second()));
     mex.append('|');
     if(supportDate.dayOfWeek() < 10)
         mex.append('0');
     mex.append(QString::number(supportDate.dayOfWeek()));
     mex.append("|-\n\r");*/
    //    if (port->isOpen())
    //        port->write(mex.toLatin1());
}
