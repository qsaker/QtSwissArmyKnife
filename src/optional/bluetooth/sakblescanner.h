﻿/***************************************************************************************************
 * Copyright 2023-2024 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#ifndef SAKBLESCANNER_H
#define SAKBLESCANNER_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLoggingCategory>
#include <QMutex>
#include <QThread>
#include <QVariant>

class SAKBleScanner : public QThread
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QVariantList deviceInfoList READ devicesInfoList NOTIFY devicesInfoListChanged)
    Q_PROPERTY(int timeoutInterval READ timeoutInterval WRITE setTimeoutInterval NOTIFY timeoutIntervalChanged)
    Q_PROPERTY(QString namefiltter READ namefiltter WRITE setNameFiltter NOTIFY filtterNameChanged)
    // clang-format on
public:
    explicit SAKBleScanner(QObject *parent = nullptr);
    ~SAKBleScanner();

public:
    Q_INVOKABLE void startDiscover();
    Q_INVOKABLE void stopDiscover();
    Q_INVOKABLE bool isActive();

    Q_INVOKABLE QVariant deviceInfo(int index);
    Q_INVOKABLE QString deviceName(const QVariant &deviceInfo);

signals:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void errorOccurred(const QString &errStr);

protected:
    virtual void run() override;

private:
    QBluetoothDeviceDiscoveryAgent *m_discover;
    QMutex m_deviceInfoListMutex;

private:
    void onDiscoveryFinished();
    void onDiscoveryErrorOccurred(QBluetoothDeviceDiscoveryAgent::Error error);
    void onDiscoveryDeviceDiscovered(const QBluetoothDeviceInfo &info);

public:
    QVariantList devicesInfoList();
    int timeoutInterval();
    void setTimeoutInterval(int interval);
    QString namefiltter();
    void setNameFiltter(const QString &flag);

signals:
    void devicesInfoListChanged();
    void enableRefreshChanged();
    void timeoutIntervalChanged();
    void filtterNameChanged();

private:
    QVector<QBluetoothDeviceInfo> m_deviceInfoList;
    int m_timeoutInterval{120};
    QString m_nameFiltter{""};
};

#endif // SAKBLESCANNER_H
