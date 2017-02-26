# Hardware
## STM32F103 Development Board

[Minimum System Development](http://www.ebay.com/itm/ARM-Cortex-M3-STM32F103C8T6-STM32-Minimum-System-Development-Board-/381374722304?hash=item58cbb47100:g:S0cAAOxyni9S~0Fd) ~ $5 from China

[STM32F103 Datasheet](http://www.st.com/content/ccc/resource/technical/document/datasheet/33/d4/6f/1d/df/0b/4c/6d/CD00161566.pdf/files/CD00161566.pdf/jcr:content/translations/en.CD00161566.pdf)

## Used Pins

Status LED to show board activity:
* PB0 - LED blinks in 500ms cycle when waiting; in 250ms cycle when USB is connected

Used for a serial connection
* PA2 - TX of UART
* PA3 - RX of UART

Serial Bootloader needs
* PA9 - TX of UART
* PA10 - RX of UART
And during the reset
* BOOT0 enabled
* BOOT1 disabled
Normal startup is with BOOT0 and BOOT1 disabled
[Source](https://www.youtube.com/watch?v=G_RF0a0hrak)

## Flashing Software
### Serial Flashing needs
* [stm32flash](https://sourceforge.net/p/stm32flash/code/ci/master/tree/)

Example usage:
./stm32flash -v -w ch.hex /dev/ttyUSB0

# Software
## Chibios
## Modules
* DS18B20 [Github source](https://github.com/part1zano/chibios-stm32f103/tree/master/ds18b20_new)
