#include "dose.h"
#include "ui_dose.h"
//#include "qextserialport.h"
//#include "qextserialenumerator.h"
#include "hled.h"
#include "qmessagebox.h"

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::updateDoseSummary(void)
{
    QSqlQuery _query;
    _query.prepare("SELECT description FROM line ORDER BY id ASC");
    _query.exec();
    if(_query.lastError().isValid())
        qDebug()<<_query.lastError();
    
    int count = 0;
    while (_query.next())
    {
        if(count == 0)
        {
            ui->lline1_1->setText(_query.value(0).toString());
            ui->lline1_2->setText(_query.value(0).toString());
            ui->lline1_3->setText(_query.value(0).toString());
            ui->lline1_4->setText(_query.value(0).toString());
            ui->lline1_5->setText(_query.value(0).toString());
            ui->lline1_6->setText(_query.value(0).toString());
            ui->lline1_7->setText(_query.value(0).toString());
            ui->cbnline_3->setItemText(count, _query.value(0).toString());
        }
        if(count == 1)
        {
            ui->lline2_1->setText(_query.value(0).toString());
            ui->lline2_2->setText(_query.value(0).toString());
            ui->lline2_3->setText(_query.value(0).toString());
            ui->lline2_4->setText(_query.value(0).toString());
            ui->lline2_5->setText(_query.value(0).toString());
            ui->lline2_6->setText(_query.value(0).toString());
            ui->lline2_7->setText(_query.value(0).toString());
            ui->cbnline_3->setItemText(count, _query.value(0).toString());
        }
        if(count == 2)
        {
            ui->lline3_1->setText(_query.value(0).toString());
            ui->lline3_2->setText(_query.value(0).toString());
            ui->lline3_3->setText(_query.value(0).toString());
            ui->lline3_4->setText(_query.value(0).toString());
            ui->lline3_5->setText(_query.value(0).toString());
            ui->lline3_6->setText(_query.value(0).toString());
            ui->lline3_7->setText(_query.value(0).toString());
            ui->cbnline_3->setItemText(count, _query.value(0).toString());
        }
        if(count == 3)
        {
            ui->lline4_1->setText(_query.value(0).toString());
            ui->lline4_2->setText(_query.value(0).toString());
            ui->lline4_3->setText(_query.value(0).toString());
            ui->lline4_4->setText(_query.value(0).toString());
            ui->lline4_5->setText(_query.value(0).toString());
            ui->lline4_6->setText(_query.value(0).toString());
            ui->lline4_7->setText(_query.value(0).toString());
            ui->cbnline_3->setItemText(count, _query.value(0).toString());
        }
        count++;
    }
    int line = 0;
    int dow = 0;
    for(dow = 1; dow < 8; dow++)
    {
        count = 0;
        for(line = 0; line < 4; line++)
        {
            _query.prepare("SELECT total(quantity) FROM timerDose WHERE id_line == ? AND dayOfWek == ?");
            _query.bindValue(0, line);
            _query.bindValue(1, dow);
            _query.exec();
            if(_query.lastError().isValid())
                qDebug()<<_query.lastError();
            
            
            while (_query.next())
            {
                if(dow == 1)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_1->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_1->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_1->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_1->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_1->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_1->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_1->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_1->setText("--");
                    }
                }
                if(dow == 2)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_2->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_2->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_2->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_2->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_2->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_2->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_2->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_2->setText("--");
                    }
                }
                if(dow == 3)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_3->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_3->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_3->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_3->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_3->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_3->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_3->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_3->setText("--");
                    }
                }
                if(dow == 4)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_4->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_4->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_4->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_4->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_4->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_4->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_4->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_4->setText("--");
                    }
                }
                if(dow == 5)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_5->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_5->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_5->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_5->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_5->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_5->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_5->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_5->setText("--");
                    }
                }
                if(dow == 6)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_6->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_6->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_6->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_6->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_6->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_6->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_6->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_6->setText("--");
                    }
                }
                if(dow == 7)
                {
                    if(line == 0)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue1_7->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue1_7->setText("--");
                    }
                    if(line == 1)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue2_7->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue2_7->setText("--");
                    }
                    if(line == 2)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue3_7->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue3_7->setText("--");
                    }
                    if(line == 3)
                    {
                        if(_query.value(0).toFloat() != 0.00)
                            ui->llvalue4_7->setText(_query.value(0).toString()+" ml");
                        else
                            ui->llvalue4_7->setText("--");
                    }
                }
                count++;
            }
        }
    }
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di

void dose::on_cbnpump_3_currentIndexChanged(int index)
{
    
    QSqlQuery query;
    query.prepare("SELECT fact_calibration FROM settings WHERE id_pump = ?");
    query.bindValue(0, index);
    try
    {
        query.exec();
    }
    catch(...)
    {
        QString err_support;
        err_support = query.lastError().text();
        QMessageBox::critical(this, tr(TITLE_APP), tr("Impossibile eseguire la query")+
                              err_support+tr("\nClick Cancel per uscire.")
                              , QMessageBox::Cancel);
        return;
    }
    while (query.next())
    {
        double out = query.value(0).toDouble();
        ui->dscalibrate->setValue(out);
    }
    
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di inserire gli item in db

void dose::on_pbInsert_released()
{
    //inserimento item in db:
    ui->pbInsert->hide();
    QSqlQuery query;
    int idOfItem = 0;
    //prima fase cerco un'item libero nel db
    query.prepare("SELECT id from timerDose WHERE row = 255");
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    
    if(query.next())
        idOfItem = query.value(0).toInt();
    else
    {//Non più item disponibili
        updateTable();
        ui->pbInsert->show();
        QMessageBox::information(this, tr(TITLE_APP),
                                 tr("Inserimento nuova configurazione oraria "
                                    " fallito, hai terminato il numero massimo di configurazioni editabili."));
        return;
    }//seconda fase cerco un'item libero in tabella
    QTableWidgetItem* item;
    int y = 0;
    for(y = 0; y < (NUM_OF_SCHEDULER); y++)
    {
        item = ui->twProg->item(y, ui->twProg->currentColumn());
        if (!item || item->text().isEmpty())
        {
            break;
        }
    }
    //terza fase inserisco l'item nel db
    query.prepare("UPDATE timerDose set time = ?, id_line = ?, quantity = ?, dayOfWek = ?, row = ? WHERE id IS ?");
    query.bindValue(0, ui->dtestart->time());
    query.bindValue(1, ui->cbnline_3->currentIndex());
    query.bindValue(2, ui->leQuantity_3->text().toLatin1());
    query.bindValue(3, ui->twProg->currentColumn() + 1);
    query.bindValue(4, y);
    query.bindValue(5, idOfItem);
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    
    
    //quarta fase faccio l'update della tabella
    updateTable();
    updateDoseSummary();
    ui->pbInsert->show();
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di rimuovere gli item dal db

void dose::on_pbRemove_released()
{
    QSqlQuery query;
    QSqlQuery subQuery;
    int support = 0;
    int numOfItem = 0;
    //Seleziono l'Item interessato e mi ricavo l'id
    int row = ui->twProg->currentRow();
    int DOW = ui->twProg->currentColumn()+1;
    query.prepare("SELECT id from timerDose WHERE row = ? AND dayOfWek = ?");
    query.bindValue(0, row);
    query.bindValue(1, DOW);
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    
    if(!query.next())
        return;
    subQuery.prepare("UPDATE timerDose set row = 255, time = 0, id_line = 0, quantity = 0.0, dayOfWek = 0 WHERE id = ?");
    subQuery.bindValue(0,query.value(0).toInt());
    subQuery.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    
    //seleziona tutti gli item appartenenti alla colonna con valore di riga superiore a quello appena eliminato
    query.prepare("SELECT id from timerDose WHERE row > ? AND dayOfWek = ?");
    query.bindValue(0, row);
    query.bindValue(1, DOW);
    query.exec();
    if(query.lastError().isValid())
        qDebug()<<query.lastError();
    
    int lastItem = 0;
    uint8_t newRowValue=ui->twProg->currentRow();
    while (query.next())
    {
        numOfItem++;
        lastItem = query.value(0).toInt();
        //qui assegno la nuova riga alla quale è shiftato l'item
        subQuery.prepare("UPDATE timerDose set row = ? WHERE id = ?");
        subQuery.bindValue(0,(newRowValue+support));
        subQuery.bindValue(1,lastItem);
        subQuery.exec();
        if(subQuery.lastError().isValid())
            qDebug()<<subQuery.lastError();
        
        support++;
    }
    //Aggiorno la tabella con i dati in db
    updateTable();
    updateDoseSummary();
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di aggiornare la tabella con i dati nel db

void dose::updateTable()
{
    int u = 0;
    int x = 0;
    for(x = 0; x < 7; x++)
    {
        for(u = 0; u < NUM_OF_SCHEDULER; u++)
        {
            QTableWidgetItem* myItem = ui->twProg->item(u,x);
            delete myItem;
        }
    }
    QSqlQuery query;
    for(u=0; u < NUM_OF_SCHEDULER; u++)
    {
        query.prepare("SELECT time, id_line, quantity, dayOfWek, row FROM timerDose WHERE id = ?");
        query.bindValue(0, u);
        query.exec();
        while (query.next())
        {
            QString time = query.value(0).toString().mid(0, 8);
            QString idPump = ui->cbnline_3->itemText(query.value(1).toInt());
            QString quantity = query.value(2).toString();
            int row = query.value(4).toInt();
            int column = query.value(3).toInt()-1;
            QTableWidgetItem* myItem = new QTableWidgetItem(time+"-"+idPump+"-"+quantity+"ml");
            myItem->setFlags(myItem->flags() ^ Qt::ItemIsEditable);
            if(row != 255 && column != 255)
                ui->twProg->setItem(row,column,myItem);
        }
    }
}


//------------------------------------------------------------------------------------------

//Handler del tasto di scrfittura schedulazioni orarie


int send_phase = 0;
void dose::on_pbWriteScheduler_released()
{
    //interrompo il timer di sincronizzazione linee
    Syncronize->stop();
    //avvio un timer di 250ms che mi richiama la funzione sottostante che inizia la scrittura delle schedulazioni orarie
    //Uso un timer per evitare la condizione pwer la quale premo questo tasto nell'esatto istante in cui il dispositivo sta inviando la sincronizzazione, e quindi ottengo un afalsa partenza
    QTimer::singleShot(500, this, SLOT(writeSchedulation()));

}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di inviare la configurazione oraria al dispositivo

void dose::writeSchedulation()
{
    timerDose_type SchedulerFrame;
    QJsonObject jsonObject;
    send_counter = 0;
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

    jsonObject.insert("CMD", 9);
    jsonObject.insert("NOI", send_counter);
    jsonObject.insert("BACON",QJsonArray()<<SchedulerFrame.ID<<SchedulerFrame.HOUR<<SchedulerFrame.MINUTE<<SchedulerFrame.EXEC<<SchedulerFrame.ID_LINE<<SchedulerFrame.QUANTITY<<SchedulerFrame.DAYOFWEEK);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    send_counter++;
}

//------------------------------------------------------------------------------------------

//Funzione che si occupa di leggere la configurazione oraria dal dispositivo

void dose::on_pbReadScheduler_released()
{
    Syncronize->stop();
    //avvio un timer di 250ms che mi richiama la funzione sottostante che inizia la scrittura delle schedulazioni orarie
    //Uso un timer per evitare la condizione pwer la quale premo questo tasto nell'esatto istante in cui il dispositivo sta inviando la sincronizzazione, e quindi ottengo un afalsa partenza
    QTimer::singleShot(500, this, SLOT(ReadSchedulation()));

}

void dose::ReadSchedulation()
{
    QJsonObject jsonObject;
    send_counter = 0;
    jsonObject.insert("CMD", 5);
    jsonObject.insert("NOI", send_counter);
    // jsonObject.insert("BACON",QJsonArray()<<SchedulerFrame[send_counter].ID<<SchedulerFrame[send_counter].HOUR<<SchedulerFrame[send_counter].MINUTE<<SchedulerFrame[send_counter].EXEC<<SchedulerFrame[send_counter].ID_LINE<<SchedulerFrame[send_counter].QUANTITY<<SchedulerFrame[send_counter].DAYOFWEEK);
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    thread.transaction(ui->cbCom->currentText(),
                       USB_SEND_TIMEOUT,//timeout risposta in mse TG5Yc
                       strJson);
    send_counter++;
}
