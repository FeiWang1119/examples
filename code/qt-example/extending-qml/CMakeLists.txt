# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# The basic steps for creating a QML extension:
# 1. Define new QML types by subclassing QObject and registering them with QML_ELEMENT or QML_NAMED_ELEMENT()
# 2. Add callable methods using Q_INVOKABLE or Qt slots, and connect to Qt signals with an onSignal syntax
# 3. Add property bindings by defining NOTIFY signals
# 4. Define custom property types if the built-in types are not sufficient
# 5. Define list property types using QQmlListProperty
# 6. Create a plugin library by defining a Qt plugin and writing a qmldir file

add_subdirectory(chapter1-basics)
add_subdirectory(chapter2-methods)
add_subdirectory(chapter3-bindings)
add_subdirectory(chapter4-customPropertyTypes)
add_subdirectory(chapter5-listproperties)
add_subdirectory(chapter6-plugins)
