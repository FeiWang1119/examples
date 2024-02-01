# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(foreign LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Gui)
qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)

add_subdirectory(library/)

qt_add_executable(foreign
    birthdayparty.cpp
    birthdayparty.h
    foreigndisplay.h
    happybirthdaysong.cpp
    happybirthdaysong.h
    person.cpp
    person.h
    main.cpp
)

target_link_libraries(foreign PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Gui
    library
)

target_include_directories(foreign PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/library"
)

qt_add_qml_module(foreign
    URI People
    QML_FILES Main.qml
    SOURCES foreigndisplay.h
    DEPENDENCIES
        QtQuick
)
