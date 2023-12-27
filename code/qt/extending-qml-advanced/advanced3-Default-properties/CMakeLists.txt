# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(default LANGUAGES CXX)

if (ANDROID)
    message(FATAL_ERROR "This project cannot be built on Android.")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Qml)
qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)

qt_add_executable(default
    birthdayparty.cpp birthdayparty.h
    main.cpp
    person.cpp person.h
)

target_link_libraries(default PUBLIC
    Qt6::Core
    Qt6::Qml
)

qt_add_qml_module(default
    URI People
    QML_FILES Main.qml
)
