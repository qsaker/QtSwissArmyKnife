/*******************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 ******************************************************************************/
#ifndef SAKSERIALPORTTRANSMITTERTOOLUI_HH
#define SAKSERIALPORTTRANSMITTERTOOLUI_HH

#include "SAKTransmitterToolUi.h"
#include "SAKSerialPortTransmitterToolUiEditor.h"

class SAKSerialPortTransmitterToolUi : public SAKTransmitterToolUi
{
    Q_OBJECT
public:
    SAKSerialPortTransmitterToolUi(QWidget *parent = nullptr);

protected:
    virtual void onBaseToolUiInitialized(SAKBaseTool *tool,
                                         const QString &settingGroup) override;
    virtual QDialog *itemEditor() override;

private:
    SAKSerialPortTransmitterToolUiEditor *mEditor;
};

#endif // SAKSERIALPORTTRANSMITTERTOOLUI_HH
