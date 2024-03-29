﻿/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#ifndef SAKUI_H
#define SAKUI_H

#include <QApplication>

#include "sak.h"
#include "sakmainwindow.h"

template<typename T>
int sakExec(int argc, char* argv[], const QString& appName, bool usingCommonMainWindow = true)
{
    sakDoSomethingBeforeAppCreated(argv, appName);

    QApplication app(argc, argv);
    if (usingCommonMainWindow) {
        SAKMainWindow* mainWindow = new SAKMainWindow();
        T* centralWidget = new T(mainWindow);
        mainWindow->setWindowTitle(appName);
        mainWindow->setCentralWidget(centralWidget);
        mainWindow->show();
        mainWindow->resize(int(qreal(mainWindow->height()) * 1.732), mainWindow->height());
    } else {
        T* widget = new T();
        widget->show();
        widget->resize(int(qreal(widget->height()) * 1.732), widget->height());
    }

    int ret = app.exec();
    sakDoSomethingAfterAppExited();
    return ret;
}

#endif // SAKUI_H
