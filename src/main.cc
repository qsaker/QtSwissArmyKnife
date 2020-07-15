﻿/*
 * Copyright 2018-2020 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project(https://www.qsak.pro). The project is an open source project. You can
 * get the source of the project from: "https://github.com/qsak/QtSwissArmyKnife"
 * or "https://gitee.com/qsak/QtSwissArmyKnife". Also, you can join in the QQ
 * group which number is 952218522 to have a communication.
 */
#include <QDebug>

#include "SAKMainWindow.hh"
#include "SAKApplication.hh"
#include "SAKSingletonController.hh"
#include "SAKSingletonErrorDialog.hh"

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, false);
    QApplication::setAttribute(Qt::AA_Use96Dpi, true);
#endif

    SAKApplication app(argc, argv);

    /// @brief 检测是够存在已运行的实例，如果存在，终止本次启动,同时激活已启动的程序
    SAKSingletonController controller;
    QObject::connect(&controller, &SAKSingletonController::showMainWindowInstanceRequest, app.mainWindow(), &SAKMainWindow::show);
    QObject::connect(&controller, &SAKSingletonController::showMainWindowInstanceRequest, app.mainWindow(), &SAKMainWindow::activateWindow);
    if (controller.isInstanceExist()){
        SAKSingletonErrorDialog dialog;
        dialog.exec();
        controller.setFlag();
        return -1024;
    }

    return app.exec();
}
