/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKTOOLBOXUI_HH
#define SAKTOOLBOXUI_HH

#include <QIcon>
#include <QList>
#include <QTimer>
#include <QWidget>
#include <QLoggingCategory>

#include "SAKToolBox.hh"
#include "SAKCommunicationToolUi.hh"

namespace Ui {
class SAKToolBoxUi;
}

class SAKCommunicationTool;
class SAKCommunicationToolUi;
class SAKToolBoxUiParameters;
class SAKToolBoxUi : public QWidget
{
    Q_OBJECT
public:
    explicit SAKToolBoxUi(QWidget *parent = nullptr);
    ~SAKToolBoxUi();
    static QList<int> supportedCommuniticationTools();
    void setupCommuniticationTool(int type);

private:
    SAKToolBoxUiParameters *mToolBoxUiParameters{nullptr};
    SAKToolBox *mToolBox{nullptr};
    SAKCommunicationTool *mCommunicationTool{nullptr};
    SAKCommunicationToolUi *mCommunicationToolUi{nullptr};
    const QLoggingCategory mLoggingCategory{"SAK.SAKToolBoxUi"};
    QTimer *mCycleSendingTimer{nullptr};

private:
    QString communiticationToolName(int type);
    QIcon communiticationToolIcon(int type);
    SAKCommunicationToolUi *communiticationToolUi(int type);
    void try2send();
    QString dateTimeContext();
    void output2ui(const QByteArray &bytes, const QVariant &context, bool isRx);

    // slots
    void onIsWorkingChanged();
    void onTooBoxBytesInputted(const QByteArray &bytes, const QVariant &context);
    void onTooBoxBytesOutputted(const QByteArray &bytes, const QVariant &context);

private:
    void init();
    void initUi();
    void initUiCommunication();
    void initUiInput();
    void initUiOutput();

    void initSettings();
    void initSettingsCommunication();
    void initSettingsInput();
    void initSettingsOutput();

    void initSignals();
    void initSignalsCommunication();
    void initSignalsInput();
    void initSignalsOutput();

private:
    Ui::SAKToolBoxUi *ui;

    // communication
    void onPushButtonCommunicationSettingsClicked();
    void onPushButtonCommunicationOpenClicked();

    // input
    void onPushButtonInputSettingsClicked();
    void onPushButtonInputSendClicked();
    void onComboBoxInputIntervelCurrentIndexChanged();
    void onComboBoxInputFormatActivated();

    // output
    void onPushButtonOutputSettingsClicked();
    void onCheckBoxOutputWrapClicked();
};

#endif // SAKTOOLBOXUI_HH