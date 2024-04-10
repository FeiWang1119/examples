python
import os,sys
sys.path.insert(0, os.environ['HOME'] + "/.gdb/")
from qt import register_qt_printers
register_qt_printers (None)
end

python
	import sys
	sys.path.insert(0, os.environ['HOME'] + "/.gdb/python")
	from libstdcxx.v6.printers import register_libstdcxx_printers
	register_libstdcxx_printers (None)
end

set print pretty on
set confirm off

dir /home/fei/repo/dtkcore
dir /home/fei/repo/dtkgui
dir /home/fei/repo/dtkwidget
dir /home/fei/repo/libxcb
dir /home/fei/repo/qtwebengine
dir /home/fei/repo/qtdeclarative/src
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/corelib
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/gui
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/widgets
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/dbus
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/plugins/platforms/xcb
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/plugins/platforms
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/plugins
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src

set environment LD_LIBRARY_PATH=/home/fei/repo/dtkwidget/build/src:/home/fei/repo/qtbase-opensource-src-5.15.8/build/lib
# set environment LD_LIBRARY_PATH=/home/fei/repo/dtkcore/build/src:/home/fei/repo/dtkgui/build/src:/home/fei/repo/dtkwidget/build/src:
# set environment LD_LIBRARY_PATH=/home/fei/repo/qtbase/build/lib /home/fei/repo/qtbase-opensource-src-5.15.8/lib
# :/home/fei/repo/qtdeclarative/build/lib/x86_64-linux-gnu:/home/fei/repo/qtdeclarative/build/lib/x86_64-linux-gnu/qt6/qml/QtQuick/Controls/
# set environment QML_IMPORT_PATH=/home/fei/repo/qtdeclarative/build/lib/x86_64-linux-gnu/qt6/qml/QtQuick/Controls/

# define printqstring
#     printf "(QString)0x%x (length=%i): \"",&$arg0,$arg0.d->size
#     set $i=0
#     while $i < $arg0.d->size
#         set $c=$arg0.d->data()[$i++]
#         if $c < 32 || $c > 127
#                 printf "\\u0x%04x", $c
#         else
#                 printf "%c", (char)$c
#         end
#     end
#     printf "\"\n"
# end
