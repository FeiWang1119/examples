// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#ifndef CHARTSPLUGIN_H
#define CHARTSPLUGIN_H

//![0]
#include <QQmlEngineExtensionPlugin>

class ChartsPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    // the Q_PLUGIN_METADATA() macro to register the plugin with the Qt meta object system.
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)
};
//![0]

#endif

