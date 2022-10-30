#!/bin/sh
# ev3php module builder for crosscompiler
# Copyright (C) 2022 Lukas Tautz
# You need to install: build-essential and php7.0-dev
echo "ev3php module builder"
echo ""
phpize
./configure --enable-ev3php CFLAGS="-O9 -Ofast" CC="arm-linux-gnueabi-gcc"
make
echo ""
echo "Build finished"
echo ""
echo "The ev3php.so file is located in: {CURRENT_DIR}/modules/ev3php.so"
