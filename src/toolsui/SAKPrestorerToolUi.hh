/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKPRESTORERTOOLUI_HH
#define SAKPRESTORERTOOLUI_HH

#include <QWidget>

namespace Ui {
class SAKPrestorerToolUi;
}

class SAKPrestorerToolUi : public QWidget
{
    Q_OBJECT
public:
    explicit SAKPrestorerToolUi(QWidget *parent = nullptr);
    ~SAKPrestorerToolUi();

private:
    Ui::SAKPrestorerToolUi *ui{nullptr};
};

#endif // SAKPRESTORERTOOLUI_HH