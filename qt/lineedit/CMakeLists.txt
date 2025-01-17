# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(lineedit LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(DtkCore REQUIRED)
find_package(DtkGui REQUIRED)
find_package(DtkWidget REQUIRED)

add_executable(lineedit
    main.cpp
    window.cpp window.h
    dlineeditex.cpp dlineeditex.h
)

target_link_libraries(lineedit PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${DtkWidget_LIBRARIES}
)

