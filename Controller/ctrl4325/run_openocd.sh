#!/bin/bash

if [ ! $UID -eq 0 ]
then
  echo "root 権限で実行してください."
  exit -1
fi


openocd \
  -f interface/stlink.cfg \
  -c "transport select hla_swd" \
  -f target/stm32l0.cfg
