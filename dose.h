#ifndef DOSE_H
#define DOSE_H

#include <QMainWindow>
//#include "qextserialport.h"
#include "hled.h"
#include "QTimer"
#include "QtSql/QtSql"
#include "usb_thread.h"

#define NUM_OF_LINE 4
#define NUM_OF_PUMP 4
//definizione tipo di variabili
#define ERROR_LINE_NOT_ABLE 0
#define ERROR_NO_PUMP_ASSOCIATED 1
#define ERROR_PUMP_ALREADY_STOPED 2
#define ERROR_LINE_NOT_FREE 3
#define ERROR_NO_RTC_COM 4
#define ERROR_NO_CALIB_VALUE 5
#define TITLE_APP "Dose"
#define USB_SEND_TIMEOUT 1000
#define NUM_OF_SCHEDULER 150//70
typedef struct {
     uint8_t ID;
     uint8_t HOUR;
     uint8_t MINUTE;
     uint8_t EXEC;
     uint8_t ID_LINE;
     float QUANTITY;
     uint8_t DAYOFWEEK;
 }timerDose_type;

namespace Ui {
class dose;
}

class QextSerialPort;
class QextSerialEnumerator;

class dose : public QMainWindow
{
    Q_OBJECT

public:
    explicit dose(QWidget *parent = 0);
    ~dose();
    QSqlDatabase StorageDB;
    timerDose_type SchedulerFrame[NUM_OF_SCHEDULER];
private slots:
    void on_pbDose_released();
    void on_cbnpump_currentIndexChanged(int index);
    void on_dscalibrate_valueChanged(double arg1);
    void on_cbnpump_3_currentIndexChanged(int index);
    void on_pbInsert_released();
    void on_pbRemove_released();
    void on_pbRefilSol_5_released();
    void on_pbRefilSol_2_released();
    void on_pbRefilSol_3_released();
    void on_pbRefilSol_4_released();
    void Sync();
    void on_leCapacitySol_2_textChanged(const QString &arg1);
    void on_leCapacitySol_3_textChanged(const QString &arg1);
    void on_leCapacitySol_4_textChanged(const QString &arg1);
    void on_leCapacitySol_5_textChanged(const QString &arg1);
    void on_leSolDesc_2_textEdited(const QString &arg1);
    void on_leSolDesc_3_textEdited(const QString &arg1);
    void on_leSolDesc_4_textEdited(const QString &arg1);
    void on_leSolDesc_5_textEdited(const QString &arg1);
    void on_cbAbleSol_2_stateChanged(int arg1);
    void on_cbAbleSol_3_stateChanged(int arg1);
    void on_cbAbleSol_4_stateChanged(int arg1);
    void on_cbAbleSol_5_stateChanged(int arg1);
    void on_cbAbleTimeSol_2_stateChanged(int arg1);
    void on_cbAbleTimeSol_3_stateChanged(int arg1);
    void on_cbAbleTimeSol_4_stateChanged(int arg1);
    void on_cbAbleTimeSol_5_stateChanged(int arg1);
    void on_pbSetTime_released();

    void on_pbBreak_released();

    void on_pbWriteScheduler_released();
    void UpdateLine();
    void on_pbReadScheduler_released();

    void on_cbAbleSol_2_toggled(bool checked);
    void on_cbAbleSol_3_toggled(bool checked);
    void on_cbAbleSol_4_toggled(bool checked);
    void on_cbAbleSol_5_toggled(bool checked);
    void on_cbAbleSol_6_toggled(bool checked);
    void on_cbAbleSol_7_toggled(bool checked);
    void on_cbAbleSol_8_toggled(bool checked);
    void on_cbAbleSol_9_toggled(bool checked);
    void UpdateStime(void);
    void updateDoseSummary(void);
    void on_pbNetConnect_released();
    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void on_pbRefresh_released();
    void on_pbStdOut_released();
    void on_pushButton_released();
    void on_twMenu_currentChanged(int index);
    void writeSchedulation();
    void ReadSchedulation();
    void dosing();
    void stopDosing();
    void on_checkBox_stateChanged(int arg1);

    void on_cbLineSlave_toggled(bool checked);

    void on_twMenu_tabBarClicked(int index);

    void on_pbSendNetCfg_released();

private:
    void on_pbPortName_editTextChanged(const QString &arg1);
    void setControlsEnabled(bool enable);
    void updateTable();
    void SyncLineElement(int element);
    Ui::dose *ui;
    MasterThread thread;
    QTimer *Syncronize;
    int remainByte;
    char dataSend[100];
    uint8_t* configptrdst;
    int send_counter;
    uint8_t SendConfiguration;
    uint8_t ReadLineStatus;
    QString preValue;
    uint32_t jsonParserErrorCounter;
    QWidget* widgetSlave;
    QObject *tankLevelObject1;
    QObject *tankLevelObject2;
    QObject *tankLevelObject3;
    QObject *tankLevelObject4;

    QObject *tankLevelObject5;
    QObject *tankLevelObject6;
    QObject *tankLevelObject7;
    QObject *tankLevelObject8;
};





#endif // DOSE_H
