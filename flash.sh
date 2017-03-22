#!/bin/bash

# Flash the Software via OpenOCD

BIN=ch.hex

OPENOCD=openocd
PROG_CFG=/usr/local/share/openocd/scripts/interface/stlink-v2.cfg
CHIP_CFG=/usr/local/share/openocd/scripts/target/stm32f1x.cfg

if [ -f update.sh ]; then
 echo "Update $BIN via script"
 bash ./update.sh
fi

if [ ! -f $BIN ]; then
  echo "There is no $BIN available"
  exit 1
fi

sudo $OPENOCD -f $PROG_CFG -f $CHIP_CFG -c "program ch.hex verify reset exit"
