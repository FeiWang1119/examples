# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(chapter4-customPropertyTypes LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
#![0]
qt_add_executable(chapter4-customPropertyTypes
    main.cpp
    piechart.cpp piechart.h
    pieslice.cpp pieslice.h
)
#![0]

target_link_libraries(chapter4-customPropertyTypes PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

#![1] for the registration to take effect
qt_add_qml_module(chapter4-customPropertyTypes
    URI Charts
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)
