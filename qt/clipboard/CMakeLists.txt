# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(clipboard LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(clipboard
    main.cpp
    window.cpp window.h
)

target_link_libraries(clipboard PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

