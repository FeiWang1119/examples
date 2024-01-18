# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(chapter5-listproperties LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(chapter5-listproperties
    main.cpp
    piechart.cpp piechart.h
    pieslice.cpp pieslice.h
)

target_link_libraries(chapter5-listproperties PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# for the registration to take effect
qt_add_qml_module(chapter5-listproperties
    URI Charts
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

