﻿/*******************************************************************************
 * Copyright 2023 Qsaker(qsaker@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife
 * project(https://github.com/qsaker/QtSwissArmyKnife).
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in
 * the root of the source code directory.
 ******************************************************************************/
#include <QApplication>

#include "sakasciiassistant.h"
#include "sakassistantcommon.h"

int main(int argc, char* argv[]) {
  QApplication* app = CreateAssistant<SAKAsciiAssistant>(
      argc, argv, QObject::tr("Ascii Assistant"), "SAK.AsciiAssistant");
  int ret = app->exec();
  app->deleteLater();

  return ret;
}
