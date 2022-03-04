#!/bin/bash

TARGET=ctrl4325

if [ ! -f $TARGET ]
then
  echo "$TARGET: Not found."
  exit -1
fi

if [ ! -d bin ]
then
  mkdir -v bin
fi

arm-none-eabi-objcopy -v -O binary $TARGET bin/$TARGET.bin
arm-none-eabi-objcopy -v -O ihex $TARGET bin/$TARGET.hex
