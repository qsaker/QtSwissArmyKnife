﻿/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#include "sakcommunicationtool.h"
#include <QTimer>

SAKCommunicationTool::SAKCommunicationTool(QObject *parent)
    : SAKBaseTool{parent}
{}

SAKCommunicationTool::~SAKCommunicationTool() {}

void SAKCommunicationTool::inputBytes(const QByteArray &bytes)
{
    if (!isEnable()) {
        return;
    }

    m_inputBytesMutex.lock();
    m_inputBytesList.append(bytes);
    m_inputBytesMutex.unlock();
}

void SAKCommunicationTool::run()
{
    QString errStr;
    if (!initialize(errStr)) {
        qWarning() << errStr;
        emit errorOccurred(errStr);
        return;
    }

    QTimer *txTimer = new QTimer();
    txTimer->setInterval(5);
    txTimer->setSingleShot(true);
    connect(txTimer, &QTimer::timeout, txTimer, [=]() {
        this->m_inputBytesMutex.lock();
        if (!m_inputBytesList.isEmpty()) {
            auto bytes = m_inputBytesList.takeFirst();
            writeBytes(bytes);
        }
        this->m_inputBytesMutex.unlock();
        txTimer->start();
    });
    txTimer->start();

    exec();
    txTimer->deleteLater();
    txTimer = nullptr;
    uninitialize();
}
