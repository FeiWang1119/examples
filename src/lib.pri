TEMPLATE = lib

isEmpty(VERSION) {
    VERSION = $$system(git describe --tags --abbrev=0)
    isEmpty(VERSION):VERSION = $$DTK_VERSION
    isEmpty(VERSION):error(VERSION is empty)
    VERSION = $$replace(VERSION, [^0-9.],)
}

ver_list = $$split(VERSION, .)

isEmpty(VER_MAJ) {
    VER_MAJ = $$first(ver_list)
}

isEmpty(VER_MIN) {
    VER_MIN = $$member(ver_list, 1, 1)
    isEmpty(VER_MIN):VER_MIN = 0
}

isEmpty(VER_PAT) {
    VER_PAT = $$member(ver_list, 2, 2)
    isEmpty(VER_PAT):VER_PAT = 0
}

isEmpty(VER_BUI) {
    VER_BUI = $$member(ver_list, 3, 3)
    isEmpty(VER_BUI):VER_BUI = 0
}

CONFIG += c++11 create_pc create_prl no_install_prl
CONFIG += no_keywords

DEFINES += QT_MESSAGELOGCONTEXT

isEmpty(PREFIX){
    PREFIX = /usr
}

isEmpty(LIB_INSTALL_DIR) {
    target.path = $$PREFIX/lib
} else {
    target.path = $$LIB_INSTALL_DIR
}

isEmpty(INCLUDE_INSTALL_DIR) {
    DTK_INCLUDEPATH = $$PREFIX/include/libdtk-$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
} else {
    DTK_INCLUDEPATH = $$INCLUDE_INSTALL_DIR/libdtk-$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}

win32* {
    DEFINES += STATIC_LIB
    CONFIG += staticlib
}
