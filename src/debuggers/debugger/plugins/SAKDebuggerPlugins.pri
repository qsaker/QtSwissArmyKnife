include($$PWD/plugin/SAKDebuggerPlugin.pri)

include($$PWD/3d/SAKPlugin3d.pri)
include($$PWD/charts/SAKPluginCharts.pri)
include($$PWD/transponders/SAKDebuggerPluginTransponders.pri)
include($$PWD/autoresponse/SAKDebuggerPluginAutoResponse.pri)
include($$PWD/timedsending/SAKDebuggerPluginTimedSending.pri)

HEADERS += \
    $$PWD/SAKDebuggerPlugins.hh

SOURCES += \
    $$PWD/SAKDebuggerPlugins.cc

INCLUDEPATH += \
    $$PWD
