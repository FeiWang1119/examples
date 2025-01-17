# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(locale LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(locale
    main.cpp
    window.cpp window.h
)

target_link_libraries(locale PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

