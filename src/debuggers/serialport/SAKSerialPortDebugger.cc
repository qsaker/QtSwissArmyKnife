﻿/*
 * Copyright 2018-2021 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 */
#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>

#include "SAKCommonDataStructure.hh"
#include "SAKSerialPortDevice.hh"
#include "SAKSerialPortDebugger.hh"
#include "SAKSerialPortController.hh"

SAKSerialPortDebugger::SAKSerialPortDebugger(int type, QString name, QWidget *parent)
    :SAKDebugger(type, name, parent)
{
    mDeviceController = new SAKSerialPortController(this);
    mDevice = new SAKSerialPortDevice(this, this);
    initializePage();
}

SAKDebugPageDevice* SAKSerialPortDebugger::device()
{
    return mDevice;
}

SAKDebugPageController *SAKSerialPortDebugger::controller()
{
    return mDeviceController;
}
