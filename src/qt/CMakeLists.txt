# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qt-example LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_subdirectory(extending-qml)
add_subdirectory(extending-qml-advanced)
add_subdirectory(event)
add_subdirectory(simple-qml)
add_subdirectory(icon)
add_subdirectory(clipboard)
add_subdirectory(dbus-chat)
