/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include "SAKTableController.hh"
#include "ui_SAKTableController.h"

SAKTableController::SAKTableController(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::SAKTableController)
{
    ui->setupUi(this);
}

SAKTableController::~SAKTableController()
{
    delete ui;
}
