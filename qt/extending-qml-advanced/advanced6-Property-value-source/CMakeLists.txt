# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(valuesource LANGUAGES CXX)


find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)
qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)

qt_add_executable(valuesource
    birthdayparty.cpp birthdayparty.h
    happybirthdaysong.cpp happybirthdaysong.h
    main.cpp
    person.cpp person.h
)

target_link_libraries(valuesource PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
)

qt_add_qml_module(valuesource
    URI People
    QML_FILES Main.qml
    DEPENDENCIES
        QtQuick
)

