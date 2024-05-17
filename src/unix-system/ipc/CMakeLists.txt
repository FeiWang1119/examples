project(ipc)

include_directories(${CMAKE_SOURCE_DIR}/utils)

add_executable(pmsg_create pmsg_create.c ${COMMON_SRC})
add_executable(pmsg_gettr pmsg_gettr.c ${COMMON_SRC})
add_executable(pmsg_send pmsg_send.c ${COMMON_SRC})
