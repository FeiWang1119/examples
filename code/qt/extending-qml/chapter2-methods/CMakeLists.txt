# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(chapter2-methods LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(chapter2-methods
    main.cpp
    piechart.cpp piechart.h
)

target_link_libraries(chapter2-methods PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

#![0] for the registration to take effect
qt_add_qml_module(chapter2-methods
    URI Charts
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

