/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include "SAKDataStructure.hh"
#include "SAKTextFormatComboBox.hh"

SAKTextFormatComboBox::SAKTextFormatComboBox(QWidget *parent)
    : QComboBox(parent)
{
    addItem("Bin", SAKDataStructure::TextFormatBin);
    addItem("Oct", SAKDataStructure::TextFormatOct);
    addItem("Dec", SAKDataStructure::TextFormatDec);
    addItem("Hex", SAKDataStructure::TextFormatHex);
    addItem("Ascii", SAKDataStructure::TextFormatAscii);
    addItem("Utf8", SAKDataStructure::TextFormatUtf8);
}
