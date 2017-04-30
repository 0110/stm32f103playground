#!/bin/bash

# Flash the Software via OpenOCD

BIN=ch.hex

OPENOCD=openocd
OPENOCD_DIR=/usr/local/share/openocd
if [ -f update.sh ]; then
 echo "Update $BIN via script"
 source update.sh
fi

PROG_CFG=$OPENOCD_DIR/scripts/interface/stlink-v2.cfg
CHIP_CFG=$OPENOCD_DIR/scripts/target/stm32f1x.cfg

if [ ! -f $BIN ]; then
  echo "There is no $BIN available"
  exit 1
fi

sudo $OPENOCD -f $PROG_CFG -f $CHIP_CFG -c "program ch.hex verify reset exit"
