dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/corelib
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/gui
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/widgets
dir /home/fei/repo/qtbase-opensource-src-5.15.8/src/dbus
dir /home/fei/repo/dtkcore
dir /home/fei/repo/dtkgui
dir /home/fei/repo/dtkwidget

define printqstring
    printf "(QString)0x%x (length=%i): \"",&$arg0,$arg0.d->size
    set $i=0
    while $i < $arg0.d->size
        set $c=$arg0.d->data()[$i++]
        if $c < 32 || $c > 127
                printf "\\u0x%04x", $c
        else
                printf "%c", (char)$c
        end
    end
    printf "\"\n"
end
