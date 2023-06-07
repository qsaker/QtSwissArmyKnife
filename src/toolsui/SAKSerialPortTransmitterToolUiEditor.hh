/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKSERIALPORTTRANSMITTERTOOLUIEDITOR_HH
#define SAKSERIALPORTTRANSMITTERTOOLUIEDITOR_HH

#include <QDialog>

namespace Ui {
class SAKSerialPortTransmitterToolUiEditor;
}

class SAKSerialPortTransmitterToolUiEditor : public QDialog
{
    Q_OBJECT

public:
    explicit SAKSerialPortTransmitterToolUiEditor(QWidget *parent = nullptr);
    ~SAKSerialPortTransmitterToolUiEditor();

private:
    Ui::SAKSerialPortTransmitterToolUiEditor *ui;
};

#endif // SAKSERIALPORTTRANSMITTERTOOLUIEDITOR_HH