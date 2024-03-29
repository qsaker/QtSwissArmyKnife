﻿/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#ifndef SAKCRCCALCULATORTOOLUI_H
#define SAKCRCCALCULATORTOOLUI_H

#include "sakbasetoolui.h"

namespace Ui {
class SAKCrcCalculatorToolUi;
}

class SAKCrcCalculatorToolUi : public SAKBaseToolUi
{
    Q_OBJECT
public:
    SAKCrcCalculatorToolUi(QWidget *parent = nullptr);
    ~SAKCrcCalculatorToolUi();

protected:
    void onIsWorkingChanged(bool isWorking) override;
    void onBaseToolUiInitialized(SAKBaseTool *tool, const QString &settingsGroup) override;

private:
    Ui::SAKCrcCalculatorToolUi *ui;
};

#endif // SAKCRCCALCULATORTOOLUI_H