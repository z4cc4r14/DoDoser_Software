/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "usb_thread.h"

#include <QtSerialPort/QSerialPort>

#include <QTime>

QT_USE_NAMESPACE

MasterThread::MasterThread(QObject *parent)
    : QThread(parent), waitTimeout(0), quit(false)
{
}

MasterThread::~MasterThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void MasterThread::transaction(const QString &portName, int waitTimeout, const QString &request)
{
    QMutexLocker locker(&mutex);
    this->portName = portName;
    this->waitTimeout = waitTimeout;
    this->request = request;
    if (!isRunning())
        start();
    else
        cond.wakeOne();
}

void MasterThread::run()
{
    bool currentPortNameChanged = false;

    mutex.lock();
    QString currentPortName;
    if (currentPortName != portName)
    {
        currentPortName = portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = waitTimeout;
    QString currentRequest = request;
    mutex.unlock();
    QSerialPort serial;

    while (!quit)
    {
        if (currentPortNameChanged)
        {
            serial.close();
            serial.setPortName(currentPortName);
            serial.setBaudRate(57600);
            if (!serial.open(QIODevice::ReadWrite))
            {
                emit error(tr("Can't open %1, error code %2")
                           .arg(portName).arg(serial.error()));
                return;
            }
        }
        // write request
        QByteArray requestData = currentRequest.toLocal8Bit();
        serial.write(requestData);
        if (serial.waitForBytesWritten(waitTimeout))
        {
            // read response
            if (serial.waitForReadyRead(currentWaitTimeout))
            {
                QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(25))//25
                    responseData += serial.readAll();

                QString response(responseData);
                emit this->response(response);
            }
            else
            {
                emit timeout(tr("Wait read response timeout %1")
                             .arg(QTime::currentTime().toString()));
            }
        }
        else
        {
            emit timeout(tr("Wait write request timeout %1")
                         .arg(QTime::currentTime().toString()));
        }
        mutex.lock();
        cond.wait(&mutex);
        if (currentPortName != portName)
        {
            currentPortName = portName;
            currentPortNameChanged = true;
        }
        else
        {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = waitTimeout;
        currentRequest = request;
        mutex.unlock();
    }
}
