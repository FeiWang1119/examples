project(ipc)

include_directories(${CMAKE_SOURCE_DIR}/utils)

add_executable(pmsg_create pmsg_create.c ${COMMON_SRC})
