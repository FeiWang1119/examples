# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(chat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/dbus/chat")

find_package(Qt6 REQUIRED COMPONENTS Core DBus Gui Widgets)

qt_standard_project_setup()

set(chat_SRCS)

# qt_add_dbus_interface(<VAR>
# dbus_spec
# basename
# )
qt_add_dbus_interface(chat_SRCS
    org.example.chat.xml
    chat_interface
)

# qt_add_dbus_adaptor(<VAR> 
#     dbus_spec 
#     header
#     [parent_class]
#     [basename] The default file and class name are generated from the last segment in the dbus_spec base name:
#     [classname] The default file and class name are generated from the last segment in the dbus_spec base name:
# )
qt_add_dbus_adaptor(chat_SRCS
    org.example.chat.xml # dbus_spec
    qobject.h # header
    QObject # parent_class
    chat_adaptor # basename option
    # classname use default
)

qt_add_executable(chat
    chat.cpp chat.h
    chatmainwindow.ui
    ${chat_SRCS}
)

set_target_properties(chat PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chat PRIVATE
    Qt6::Core
    Qt6::DBus
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS chat
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
