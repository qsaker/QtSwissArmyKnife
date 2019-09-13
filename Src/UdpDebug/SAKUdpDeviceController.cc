﻿/*
 * Copyright (C) 2018-2019 wuuhii. All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project. The project is a open source project, you can get the source from:
 *     https://github.com/wuuhii/QtSwissArmyKnife
 *     https://gitee.com/wuuhii/QtSwissArmyKnife
 *
 * If you want to know more about the project, please join our QQ group(952218522).
 * In addition, the email address of the project author is wuuhii@outlook.com.
 * Welcome to bother.
 *
 * I write the comment in English, it's not because that I'm good at English,
 * but for "installing B".
 */
#include <QList>
#include <QMetaEnum>
#include <QLineEdit>
#include <QSerialPortInfo>

#include "SAKBase.hh"
#include "SAKSerialportAssistantController.hh"
#include "ui_SAKSerialportAssistantController.h"
SAKSerialportAssistantController::SAKSerialportAssistantController(QWidget *parent)
    :QWidget (parent)
    ,ui (new Ui::SAKSerialportAssistantController)
{
    ui->setupUi(this);

    comboBoxSerialports      = ui->comboBoxSerialports;
    comboBoxBaudrate         = ui->comboBoxBaudrate;
    comboBoxDatabits         = ui->comboBoxDatabits;
    comboBoxStopbits         = ui->comboBoxStopbits;
    comboBoxParity           = ui->comboBoxParity;
    checkBoxCustomBaudrate   = ui->checkBoxCustomBaudrate;

    refresh();
}

SAKSerialportAssistantController::~SAKSerialportAssistantController()
{
    delete ui;
}

void SAKSerialportAssistantController::refresh()
{
    SAKBase::instance()->initComComboBox(comboBoxSerialports);
    SAKBase::instance()->initBaudRateComboBox(comboBoxBaudrate);
    SAKBase::instance()->initDataBitsComboBox(comboBoxDatabits);
    SAKBase::instance()->initStopBitsComboBox(comboBoxStopbits);
    SAKBase::instance()->initParityComboBox(comboBoxParity);
}

void SAKSerialportAssistantController::setUiEnable(bool enable)
{
    comboBoxSerialports->setEnabled(enable);
    comboBoxBaudrate->setEnabled(enable);
    comboBoxDatabits->setEnabled(enable);
    comboBoxStopbits->setEnabled(enable);
    comboBoxParity->setEnabled(enable);
    checkBoxCustomBaudrate->setEnabled(enable);
}

enum QSerialPort::DataBits SAKSerialportAssistantController::dataBits()
{
    return static_cast<QSerialPort::DataBits>(comboBoxDatabits->currentData().toInt());
}

enum QSerialPort::StopBits SAKSerialportAssistantController::stopBits()
{
    return static_cast<QSerialPort::StopBits>(comboBoxStopbits->currentData().toInt());
}

enum QSerialPort::Parity SAKSerialportAssistantController::parity()
{
    return static_cast<QSerialPort::Parity>(comboBoxParity->currentData().toInt());
}

QString SAKSerialportAssistantController::name()
{
    QString portName = comboBoxSerialports->currentText();
    portName = portName.split(' ').first();
    return  portName;
}

qint32 SAKSerialportAssistantController::baudRate()
{
    qint32 rate = 9600;
    bool ok = false;
    if (comboBoxBaudrate->currentText().isEmpty()){
        return 9600;
    }

    rate = comboBoxBaudrate->currentText().toInt(&ok);
    if (!ok){
        rate = 9600;
    }

    return rate;
}

void SAKSerialportAssistantController::on_checkBoxCustomBaudrate_clicked()
{
    if (checkBoxCustomBaudrate->isChecked()){
        comboBoxBaudrate->setEditable(true);
        comboBoxBaudrate->lineEdit()->selectAll();
        comboBoxBaudrate->lineEdit()->setFocus();
    }else{
        comboBoxBaudrate->setEditable(false);
    }
}
