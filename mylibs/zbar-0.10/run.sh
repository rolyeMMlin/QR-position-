#!/bin/bash
export CFLAGS=""
export NM=nm
./configure --prefix="/home/firefly/Work/mylibs/zbar" --host=arm-linux --enable-shared --enable-static --without-imagemagick --without-jpeg --without-python --without-gtk --without-qt --disable-video -build=arm
make clean
make 
make install


