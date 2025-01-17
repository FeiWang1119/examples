# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT ANDROID)
    add_subdirectory(advanced1-Base-project)
    add_subdirectory(advanced2-Inheritance-and-coercion)
    add_subdirectory(advanced3-Default-properties)
endif(NOT ANDROID)
add_subdirectory(advanced4-Grouped-properties)
add_subdirectory(advanced5-Attached-properties)
add_subdirectory(advanced6-Property-value-source)
add_subdirectory(advanced7-Foreign-objects-integration)
