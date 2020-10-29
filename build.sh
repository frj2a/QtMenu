#!/bin/bash
if [ -e Makefile ]
then
    make clean -j4
    make distclean
fi
QT_OTIMIZA="linux-g++"
MAQUINA=`uname -m`
lrelease iView.pro 2> /dev/null
if [ "$MAQUINA" = "x86_64" ]
then
        QT_OTIMIZA="linux-g++-64"
fi
qmake menu.pro -spec $QT_OTIMIZA "CONFIG-=debug release debug_and_release" "CONFIG+=release" && make qmake_all 1> /dev/null 2> /dev/null
# make  $MAKEOPTS && strip release/menu && upx --best --ultra-brute menu && A=`tempfile` && rm -f $A ; mkdir $A && mv release/menu $A && make distclean && mv $A/menu .
make -s $MAKEOPTS && strip release/menu &&                                  A=`tempfile` && rm -f $A            && mv release/menu $A && make distclean && mv $A menu && rm -fR GeneratedFiles/ release/ debug/
