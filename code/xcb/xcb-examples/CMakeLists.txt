project(xcb-examples)

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

add_executable(screenInfo screenInfo.c)
add_executable(xcbwindow xcbwindow.c)
add_executable(gcontext gcontext.c)
add_executable(gcontext_demo gcontext_demo.c)
add_executable(event_demo event_demo.c)

target_link_libraries(screenInfo PRIVATE PkgConfig::XCB)
target_link_libraries(xcbwindow PRIVATE PkgConfig::XCB)
target_link_libraries(gcontext PRIVATE PkgConfig::XCB)
target_link_libraries(gcontext_demo PRIVATE PkgConfig::XCB)
target_link_libraries(event_demo PRIVATE PkgConfig::XCB)
