﻿/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#include "sakanalyzertool.h"
#include "sakinterface.h"

SAKAnalyzerTool::SAKAnalyzerTool(QObject *parent)
    : SAKBaseTool{parent}
{
    m_enable = false;
}

void SAKAnalyzerTool::setFixed(bool fixed)
{
    mParametersMutex.lock();
    mParameters.fixed = fixed;
    mParametersMutex.unlock();
}

void SAKAnalyzerTool::setFrameBytes(int bytes)
{
    mParametersMutex.lock();
    mParameters.frameBytes = bytes;
    mParametersMutex.unlock();
}

void SAKAnalyzerTool::setSeparationMark(const QByteArray &mark)
{
    mParametersMutex.lock();
    mParameters.separationMark = mark;
    mParametersMutex.unlock();
}

void SAKAnalyzerTool::setMaxTempBytes(int maxBytes)
{
    mParametersMutex.lock();
    mParameters.maxTempBytes = maxBytes;
    mParametersMutex.unlock();
}

void SAKAnalyzerTool::inputBytes(const QByteArray &bytes)
{
    if (bytes.isEmpty()) {
        qInfo() << "Empty input bytes, the operation will be ignored!";
        return;
    }

    QString hex = QString::fromLatin1(SAKInterface::arrayToHex(bytes, ' '));
    
    if (isEnable()) {
        mInputtedBytesMutex.lock();
        mInputtedBytes.append(bytes);
        mInputtedBytesMutex.unlock();
    } else {
        QByteArray ba = SAKInterface::arrayToHex(bytes, ' ');
        QString hex = QString::fromLatin1(ba);
        emit bytesOutput(bytes);
    }
}

void SAKAnalyzerTool::run()
{
    QTimer *handleTimer = new QTimer();
    handleTimer->setInterval(5);
    handleTimer->setSingleShot(true);
    connect(handleTimer, &QTimer::timeout, handleTimer, [=]() {
        if (m_enable) {
            mInputtedBytesMutex.lock();
            analyze();
            mInputtedBytesMutex.unlock();
        }
        handleTimer->start();
    });
    handleTimer->start();

    exec();

    handleTimer->stop();
    handleTimer->deleteLater();
    handleTimer->stop();
    handleTimer->deleteLater();

    mInputtedBytesMutex.lock();
    mInputtedBytes.clear();
    mInputtedBytesMutex.unlock();
}

void SAKAnalyzerTool::analyze()
{
    mParametersMutex.lock();
    auto ctx = mParameters;
    mParametersMutex.unlock();

    if (ctx.fixed) {
        analyzeFixed();
    } else {
        analyzeSeparationMark();
    }

    if (mInputtedBytes.length() > ctx.maxTempBytes) {
        QByteArray ba = SAKInterface::arrayToHex(mInputtedBytes, ' ');
        qInfo() << "clear bytes: " + QString::fromLatin1(ba);
        emit bytesOutput(mInputtedBytes);
        mInputtedBytes.clear();
    }
}

void SAKAnalyzerTool::analyzeFixed()
{
    mParametersMutex.lock();
    auto ctx = mParameters;
    mParametersMutex.unlock();

    while (mInputtedBytes.length() >= ctx.frameBytes) {
        QByteArray frame(mInputtedBytes.data(), ctx.frameBytes);
        mInputtedBytes.remove(0, ctx.frameBytes);

        QByteArray ba = SAKInterface::arrayToHex(frame, ' ');
        QString hex = QString::fromLatin1(ba);
        qInfo() << QString("Analyzer->%1").arg(hex);
        emit bytesOutput(frame);
    }
}

void SAKAnalyzerTool::analyzeSeparationMark()
{
    if (mInputtedBytes.isEmpty()) {
        return;
    }

    mParametersMutex.lock();
    auto ctx = mParameters;
    mParametersMutex.unlock();
    if (ctx.separationMark.isEmpty()) {
        QByteArray ba = SAKInterface::arrayToHex(mInputtedBytes, ' ');
        QString hex = QString::fromLatin1(ba);
        QString msg = QString("Analyzer->%1").arg(hex);
        qInfo() << msg;
        emit bytesOutput(mInputtedBytes);
        mInputtedBytes.clear();
        return;
    }

    auto ret = mInputtedBytes.indexOf(ctx.separationMark);
    if (ret == -1) {
        return;
    }

    int len = ret + ctx.separationMark.length();
    QByteArray frame(mInputtedBytes.constData(), len);
    mInputtedBytes.remove(0, len);

    QByteArray ba = SAKInterface::arrayToHex(frame, ' ');
    QString hex = QString::fromLatin1(ba);
    QString msg = QString("Analyzer->%1").arg(hex);
    qInfo() << msg;
    emit bytesOutput(frame);
}
