# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(icon LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(icon
    main.cpp
    window.cpp window.h
)

target_link_libraries(icon PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

