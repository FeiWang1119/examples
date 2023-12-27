# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(grouped LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Gui)
qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)

qt_add_executable(grouped
    birthdayparty.cpp birthdayparty.h
    main.cpp
    person.cpp person.h
)

target_link_libraries(grouped PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Gui
)

qt_add_qml_module(grouped
    URI People
    QML_FILES Main.qml
    DEPENDENCIES
        QtQuick
)

