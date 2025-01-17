# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

project(pingpong LANGUAGES CXX)

if (ANDROID)
    message(FATAL_ERROR "This project cannot be built on Android.")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core DBus)

qt_add_executable(ping
    ping.cpp
    ping-common.h
)

target_link_libraries(ping PRIVATE
    Qt6::Core
    Qt6::DBus
)

qt_add_executable(pong
    ping-common.h
    pong.cpp
)

target_link_libraries(pong PRIVATE
    Qt6::Core
    Qt6::DBus
)
