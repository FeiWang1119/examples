project(xcb-xlib)

find_package(X11 REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(
  XCB
  REQUIRED
  IMPORTED_TARGET
  x11-xcb
  xi
  xcb-renderutil
  sm
  ice
  xcb-render
  dbus-1
  xcb
  xcb-image
  xcb-icccm
  xcb-sync
  xcb-xfixes
  xcb-shm
  xcb-randr
  xcb-shape
  xcb-keysyms
  xcb-xkb
  xcb-composite
  xkbcommon-x11
  xcb-damage
  xcb-xinerama
  mtdev
  egl)

add_executable(xcb-xlib xcb-xlib.c)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::XCB)
target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
