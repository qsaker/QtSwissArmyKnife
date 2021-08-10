﻿/****************************************************************************************
 * Copyright 2018-2021 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 ***************************************************************************************/
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QJsonArray>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonObject>
#include <QApplication>
#include <QJsonDocument>
#include <QStandardPaths>

#include "SAKDebugger.hh"
#include "SAKApplication.hh"
#include "SAKCommonDataStructure.hh"
#include "SAKDebuggerPluginAutoResponse.hh"

SAKDebuggerPluginAutoResponse::SAKDebuggerPluginAutoResponse(
        QSettings *settings,
        QString settingsGroup,
        QSqlDatabase *sqlDatabase,
        QString tableNameSuffix,
        QWidget *parent
        )
    :SAKBaseListWidget(sqlDatabase, settings, settingsGroup, tableNameSuffix, parent)
    ,mSettiings(settings)
    ,mSqlDatabase(sqlDatabase)
    ,mSqlQuery(*sqlDatabase)
    ,mForbidAll(false)
{
    mTableCtx.tableName = mTableName;
    createSqlDatabaseTable();
    readInRecord();
}

SAKDebuggerPluginAutoResponse::~SAKDebuggerPluginAutoResponse()
{

}

void SAKDebuggerPluginAutoResponse::onBytesRead(const QByteArray &bytes)
{
    if (!mForbidAll) {
        emit bytesRead(bytes);
    }
}

void SAKDebuggerPluginAutoResponse::insertRecord(const QString &tableName,
                                                 QWidget *itemWidget)
{
    auto cookedItemWidget
            = qobject_cast<SAKDebuggerPluginAutoResponseItem*>(itemWidget);
    if (!cookedItemWidget) {
        return;
    }

    auto itemCtx = cookedItemWidget->context();
    auto tableCtx = mTableCtx;
    QString queryString = QString("INSERT INTO %1(").arg(tableName);
    queryString.append(tableCtx.columns.id).append(",");
    queryString.append(tableCtx.columns.name).append(",");
    queryString.append(tableCtx.columns.referenceData).append(",");
    queryString.append(tableCtx.columns.responseData).append(",");
    queryString.append(tableCtx.columns.enable).append(",");
    queryString.append(tableCtx.columns.referenceFormat).append(",");
    queryString.append(tableCtx.columns.responseFormat).append(",");
    queryString.append(tableCtx.columns.option).append(",");
    queryString.append(tableCtx.columns.delay).append(",");
    queryString.append(tableCtx.columns.interval).append(")");
    queryString.append("VALUES(");
    queryString.append(QString("%1,").arg(itemCtx.id));
    queryString.append(QString("'%1',").arg(itemCtx.name));
    queryString.append(QString("'%1',").arg(itemCtx.referenceData));
    queryString.append(QString("'%1',").arg(itemCtx.responseData));
    queryString.append(QString("%1,").arg(itemCtx.enable));
    queryString.append(QString("%1,").arg(itemCtx.referenceFormat));
    queryString.append(QString("%1,").arg(itemCtx.responseFormat));
    queryString.append(QString("%1,").arg(itemCtx.option));
    queryString.append(QString("%1,").arg(itemCtx.delay));
    queryString.append(QString("%1)").arg(itemCtx.interval));
    if (!mSqlQuery.exec(queryString)) {
        qInfo() << queryString;
        qWarning() << "Insert record to " << tableCtx.tableName
                   << " table failed: " << mSqlQuery.lastError().text();
    }
}

QWidget *SAKDebuggerPluginAutoResponse::createItemFromParameters(
        const QJsonObject &jsonObj
        )
{
    if (jsonObj.isEmpty()) {
        return new SAKDebuggerPluginAutoResponseItem;
    } else {
        SAKDebuggerPluginAutoResponseItem::SAKStructItemContext itemCtx;
        itemCtx.id = jsonObj.value(mTableCtx.columns.id).toVariant().toULongLong();
        itemCtx.name = jsonObj.value(mTableCtx.columns.id).toString();
        itemCtx.referenceData = jsonObj.value(mTableCtx.columns.id).toString();
        itemCtx.responseData = jsonObj.value(mTableCtx.columns.id).toString();
        itemCtx.enable = jsonObj.value(mTableCtx.columns.id).toBool();
        itemCtx.referenceFormat = jsonObj.value(mTableCtx.columns.id).toInt();
        itemCtx.responseFormat = jsonObj.value(mTableCtx.columns.id).toInt();
        itemCtx.option = jsonObj.value(mTableCtx.columns.id).toInt();
        itemCtx.delay = jsonObj.value(mTableCtx.columns.id).toBool();
        itemCtx.interval = jsonObj.value(mTableCtx.columns.id).toInt();

        return new SAKDebuggerPluginAutoResponseItem(itemCtx);
    }
}

QJsonObject SAKDebuggerPluginAutoResponse::toJsonObject(QWidget *itemWidget)
{
    auto cookedItemWidget =
            qobject_cast<SAKDebuggerPluginAutoResponseItem*>(itemWidget);
    auto itemCtx = cookedItemWidget->context();
    QJsonObject jsonObj;
    jsonObj.insert(mTableCtx.columns.id, qint64(itemCtx.id));
    jsonObj.insert(mTableCtx.columns.name, itemCtx.name);
    jsonObj.insert(mTableCtx.columns.referenceData, itemCtx.referenceData);
    jsonObj.insert(mTableCtx.columns.responseData, itemCtx.responseData);
    jsonObj.insert(mTableCtx.columns.enable, itemCtx.enable);
    jsonObj.insert(mTableCtx.columns.referenceFormat, itemCtx.referenceFormat);
    jsonObj.insert(mTableCtx.columns.responseFormat, itemCtx.responseFormat);
    jsonObj.insert(mTableCtx.columns.option, itemCtx.option);
    jsonObj.insert(mTableCtx.columns.delay, itemCtx.delay);
    jsonObj.insert(mTableCtx.columns.interval, qint64(itemCtx.interval));
    jsonObj.insert(mTableCtx.columns.id, qint64(itemCtx.id));

    return jsonObj;
}

quint64 SAKDebuggerPluginAutoResponse::itemId(QWidget *itemWidget)
{
    auto cookedItemWidget =
            qobject_cast<SAKDebuggerPluginAutoResponseItem*>(itemWidget);
    return cookedItemWidget->context().id;
}

void SAKDebuggerPluginAutoResponse::connectSignalsToSlots(QWidget *itemWidget)
{
    auto cookedItemWidget =
            qobject_cast<SAKDebuggerPluginAutoResponseItem*>(itemWidget);
    connect(this, &SAKDebuggerPluginAutoResponse::bytesRead,
            cookedItemWidget, &SAKDebuggerPluginAutoResponseItem::onBytesRead);

    connect(cookedItemWidget, &SAKDebuggerPluginAutoResponseItem::responseBytes,
            this, &SAKDebuggerPluginAutoResponse::writeBytes);
}

void SAKDebuggerPluginAutoResponse::readInRecord()
{
    const QString queryString = QString("SELECT * FROM %1")
            .arg(mTableCtx.tableName);
    if (mSqlQuery.exec(queryString)) {
        SAKDebuggerPluginAutoResponseItem::SAKStructItemContext itemCtx;
        while (mSqlQuery.next()) {
            QString column;
            QVariant valueVariant;

            column = mTableCtx.columns.id;
            valueVariant = mSqlQuery.value(column);
            itemCtx.id = valueVariant.toULongLong();

            column = mTableCtx.columns.name;
            valueVariant = mSqlQuery.value(column);
            itemCtx.name = valueVariant.toString();

            column = mTableCtx.columns.referenceData;
            valueVariant = mSqlQuery.value(column);
            itemCtx.referenceData = valueVariant.toString();

            column = mTableCtx.columns.responseData;
            valueVariant = mSqlQuery.value(column);
            itemCtx.responseData =valueVariant.toString();

            column = mTableCtx.columns.enable;
            valueVariant = mSqlQuery.value(column);
            itemCtx.enable = valueVariant.toBool();

            column = mTableCtx.columns.referenceFormat;
            valueVariant = mSqlQuery.value(column);
            itemCtx.referenceFormat = valueVariant.toUInt();

            column = mTableCtx.columns.responseFormat;
            valueVariant = mSqlQuery.value(column);
            itemCtx.responseFormat = valueVariant.toUInt();

            column = mTableCtx.columns.option;
            valueVariant = mSqlQuery.value(column);
            itemCtx.option = valueVariant.toUInt();

            column = mTableCtx.columns.delay;
            valueVariant = mSqlQuery.value(column);
            itemCtx.delay = valueVariant.toBool();

            column = mTableCtx.columns.interval;
            valueVariant = mSqlQuery.value(column);
            itemCtx.interval = valueVariant.toInt();

            auto *item = new QListWidgetItem();
            auto *itemWidget = new SAKDebuggerPluginAutoResponseItem(itemCtx);
            setupItemWidget(item, itemWidget);
        }
    } else {
        qWarning() << "Select record form "
                   << mTableCtx.tableName
                   << " table failed: "
                   << mSqlQuery.lastError().text();
    }
}

void SAKDebuggerPluginAutoResponse::createSqlDatabaseTable()
{
    if (!mSqlDatabase->tables().contains(mTableName)) {
        QString queryString;
        queryString.append(QString("CREATE TABLE %1(")
                           .arg(mTableName));
        queryString.append(QString("%1 INTEGER PRIMARY KEY NOT NULL,")
                           .arg(mTableCtx.columns.id));

        queryString.append(QString("%1 TEXT NOT NULL,")
                           .arg(mTableCtx.columns.name));

        queryString.append(QString("%1 TEXT NOT NULL,")
                           .arg(mTableCtx.columns.referenceData));

        queryString.append(QString("%1 TEXT NOT NULL,")
                           .arg(mTableCtx.columns.responseData));

        queryString.append(QString("%1 INTEGER NOT NULL,")
                           .arg(mTableCtx.columns.enable));

        queryString.append(QString("%1 INTEGER NOT NULL,")
                           .arg(mTableCtx.columns.referenceFormat));

        queryString.append(QString("%1 INTEGER NOT NULL,")
                           .arg(mTableCtx.columns.responseFormat));

        queryString.append(QString("%1 INTEGER NOT NULL,")
                           .arg(mTableCtx.columns.option));

        queryString.append(QString("%1 INTEGER NOT NULL,")
                           .arg(mTableCtx.columns.delay));

        queryString.append(QString("%1 INTEGER NOT NULL)")
                           .arg(mTableCtx.columns.interval));

        if (!mSqlQuery.exec(queryString)) {
            qInfo() << queryString;
            qWarning() << mSqlQuery.lastError().text();
        }
    }
}
