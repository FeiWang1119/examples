set(BIN_NAME simple-qml)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

add_executable(${BIN_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
)

target_compile_options(${BIN_NAME} PRIVATE "-fpic")

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Quick 
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

