#!/bin/bash
if [ -e Makefile ]
then
    make distclean
fi
qmake menu.pro -spec linux-g++-64 "CONFIG-=debug release debug_and_release" "CONFIG+=release" && make qmake_all
# make  $MAKEOPTS && strip menu && upx --best --ultra-brute menu && A=`tempfile` && rm -f $A ; mkdir $A && mv menu $A && make distclean && mv $A/menu .
make -s $MAKEOPTS && strip menu &&                                  A=`tempfile` && rm -f $A ;          && mv menu $A && make distclean && mv $A menu && rm -fR GeneratedFiles/ release/ debug/
