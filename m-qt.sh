#!/bin/bash

#echo yes | ./configure -opensource -developer-build -release -little-endian -shared -no-largefile -qt-sql-sqlite -no-qt3support -no-xmlpatterns -no-mmx -no-3dnow -no-sse -no-sse2 -no-svg -no-webkit -qt-zlib -qt-gif -qt-libtiff -qt-libpng -qt-libmng -qt-libjpeg -make libs -make examples -nomake tools -nomake docs -nomake demo -no-nis -no-cups -no-iconv -no-dbus -no-openssl -xplatform qws/linux-mips-g++ -qt-freetype -depths 8,16,24,32 -qt-gfx-linuxfb -qt-gfx-transformed -no-gfx-multiscreen -no-gfx-vnc -no-gfx-qvfb -no-glib -I$TSLIBDIR/include -L$TSLIBDIR/lib -prefix /usr/local/Trolltech/Qt-4.7.1-mips &&

echo yes | ./configure -opensource -release -little-endian -shared -no-largefile -qt-sql-sqlite -no-qt3support -no-xmlpatterns -no-mmx -no-3dnow -no-sse -no-sse2 -no-svg -no-webkit -qt-zlib -qt-gif -qt-libtiff -qt-libpng -qt-libmng -qt-libjpeg -make libs -nomake tools -nomake examples -nomake docs -nomake demo -no-nis -no-cups -no-iconv -no-dbus -no-openssl -xplatform qws/linux-mips-g++ -embedded mips -qt-freetype -depths 8,16,24,32 -qt-gfx-linuxfb -qt-gfx-transformed -no-gfx-multiscreen -no-gfx-vnc -no-gfx-qvfb -no-glib  -prefix /usr/local/Trolltech/Qt-4.7.1-mips/ 

#make &&

