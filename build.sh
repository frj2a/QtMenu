#!/bin/bash
# "$Date: 2019-01-24 16:35:14 -0200 (qui, 24 jan 2019) $"
# "$Author: chico $"
# "$Revision: 124 $"
if [ -e Makefile ]
then
    make distclean
fi
svn up
cd /home/chico/workspace/trunk/menu/
qmake menu.pro -spec linux-g++-64 "QMAKE_CFLAGS_ISYSTEM=-I" CONFIG-="debug release debug_and_release" CONFIG+=release && /usr/bin/make qmake_all
# make $MAKEOPTS && strip menu && upx --best --ultra-brute menu && A=`tempfile` && rm -f $A ; mkdir $A && mv menu $A && make distclean && mv $A/menu .
make -s $MAKEOPTS && strip release/menu &&                                  A=`tempfile` && rm -f $A ; mkdir $A && mv release/menu $A && make distclean && mv $A/menu .
