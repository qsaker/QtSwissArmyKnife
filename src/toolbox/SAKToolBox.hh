/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKTOOLBOX_HH
#define SAKTOOLBOX_HH

#include <QObject>
#include <QVariant>

#include "SAKBaseTool.hh"
#include "SAKMaskerTool.hh"
#include "SAKStorerTool.hh"
#include "SAKEmitterTool.hh"
#include "SAKAnalyzerTool.hh"
#include "SAKPrestorerTool.hh"
#include "SAKResponserTool.hh"
#include "SAKVelometerTool.hh"
#include "SAKStatisticianTool.hh"
#include "SAKCommunicationTool.hh"

class SAKToolBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant communicaton READ communicaton
                   NOTIFY communicatonChanged)
    Q_PROPERTY(QVariant txMasker READ txMasker CONSTANT)
    Q_PROPERTY(QVariant rxMasker READ rxMasker CONSTANT)
    Q_PROPERTY(QVariant txAnalyzer READ txAnalyzer CONSTANT)
    Q_PROPERTY(QVariant rxAnalyzer READ rxAnalyzer CONSTANT)
    Q_PROPERTY(QVariant emitter READ emitter CONSTANT)
    Q_PROPERTY(QVariant responser READ responser CONSTANT)
    Q_PROPERTY(QVariant storer READ storer CONSTANT)
    Q_PROPERTY(QVariant prestorer READ prestorer CONSTANT)
    Q_PROPERTY(QVariant rxVelometer READ rxVelometer CONSTANT)
    Q_PROPERTY(QVariant txVelometer READ txVelometer CONSTANT)
    Q_PROPERTY(QVariant rxStatistician READ rxStatistician CONSTANT)
    Q_PROPERTY(QVariant txStatistician READ txStatistician CONSTANT)

    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
public:
    explicit SAKToolBox(QObject *parent = nullptr);

    /// You must call the interface before useing.
    Q_INVOKABLE void initialize(int type);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();
    Q_INVOKABLE void send(const QByteArray &bytes,
                          const QVariant &context = QJsonObject());
    bool isWorking(){return mIsWorking;}

    SAKCommunicationTool*getCommunicationTool(){return mComunicationTool;}
    SAKMaskerTool       *getTxMaskerTool(){return mTxMaskerTool;}
    SAKMaskerTool       *getRxMaskerTool(){return mRxMaskerTool;}
    SAKAnalyzerTool     *getTxAnalyzerTool(){return mTxAnalyzerTool;}
    SAKAnalyzerTool     *getRxAnalyzerTool(){return mRxAnalyzerTool;}
    SAKEmitterTool      *getEmitterTool(){return mEmitterTool;}
    SAKResponserTool    *getResponserTool(){return mResponserTool;}
    SAKStorerTool       *getStorerTool(){return mStorerTool;}
    SAKPrestorerTool    *getPrestorerTool(){return mPrestorerTool;}
    SAKVelometerTool    *getRxVelometerTool(){return mRxVelometerTool;}
    SAKVelometerTool    *getTxVelometerTool(){return mTxVelometerTool;}
    SAKStatisticianTool *getRxStatisticianTool(){return mRxStatisticianTool;}
    SAKStatisticianTool *getTxStatisticianTool(){return mTxStatisticianTool;}

private:
    SAKCommunicationTool*mComunicationTool{nullptr};
    SAKMaskerTool       *mTxMaskerTool{nullptr};
    SAKMaskerTool       *mRxMaskerTool{nullptr};
    SAKAnalyzerTool     *mTxAnalyzerTool{nullptr};
    SAKAnalyzerTool     *mRxAnalyzerTool{nullptr};
    SAKEmitterTool      *mEmitterTool{nullptr};
    SAKResponserTool    *mResponserTool{nullptr};
    SAKStorerTool       *mStorerTool{nullptr};
    SAKPrestorerTool    *mPrestorerTool{nullptr};
    SAKVelometerTool    *mRxVelometerTool{nullptr};
    SAKVelometerTool    *mTxVelometerTool{nullptr};
    SAKStatisticianTool *mRxStatisticianTool{nullptr};
    SAKStatisticianTool *mTxStatisticianTool{nullptr};

    QList<SAKBaseTool*> mToolList;
    const QLoggingCategory mLoggingCategory{"SAK.CustomBox"};
    bool mIsWorking{false};

private:
    void uninitializedTips();

    // Properties ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
private:
    QVariant communicaton(){return QVariant::fromValue(mComunicationTool);}
    QVariant txMasker(){return QVariant::fromValue(mTxMaskerTool);}
    QVariant rxMasker(){return QVariant::fromValue(mRxMaskerTool);}
    QVariant txAnalyzer(){return QVariant::fromValue(mTxAnalyzerTool);}
    QVariant rxAnalyzer(){return QVariant::fromValue(mRxAnalyzerTool);}
    QVariant emitter(){return QVariant::fromValue(mEmitterTool);}
    QVariant responser(){return QVariant::fromValue(mResponserTool);}
    QVariant storer(){return QVariant::fromValue(mStorerTool);}
    QVariant prestorer(){return QVariant::fromValue(mPrestorerTool);}
    QVariant rxVelometer(){return QVariant::fromValue(mRxVelometerTool);}
    QVariant txVelometer(){return QVariant::fromValue(mTxVelometerTool);}
    QVariant rxStatistician(){return QVariant::fromValue(mRxStatisticianTool);}
    QVariant txStatistician(){return QVariant::fromValue(mTxStatisticianTool);}

signals:
    void isWorkingChanged();
    void communicatonChanged();
};

#endif // SAKTOOLBOX_H
