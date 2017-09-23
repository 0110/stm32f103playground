/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "shell.h"
#include "chprintf.h"

#define PRINT_UART1	SD1
#define PRINT( ... ) chprintf((BaseSequentialStream *) &PRINT_UART1, __VA_ARGS__);/**< Uart print */

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)


/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

static const ShellCommand commands[] = {
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&PRINT_UART1,
  commands
};

/*===========================================================================*/
/* Generic code.                                                             */
/*===========================================================================*/

/*
 * Blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static __attribute__((noreturn)) THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    systime_t time = 250;
    palClearPad(GPIOB, GPIOB_LED);
    chThdSleepMilliseconds(time);
    palSetPad(GPIOB, GPIOB_LED);
    chThdSleepMilliseconds(time);
  }
}

static const GPTConfig gpt4cfg = {
  1000000, // 1 MHz timer clock.
  NULL, // No callback
  0, 0
};

/*
 * Application entry point.
 */
int __attribute__((noreturn)) main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 6 and SDC driver 1 using default
   * configuration.
   */
  sdStart(&PRINT_UART1, NULL);

  /*
   * Shell manager initialization.
   */
  shellInit();

  /*
   * Creates the blinker thread.
   */
  palSetPadMode(GPIOB, GPIOB_LED, PAL_MODE_OUTPUT_PUSHPULL);
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /* Prepare debugging for DS18B20 */
  palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
  palWritePad(GPIOA, 5, 1);

  PRINT("\x1b[1J\x1b[0;0HStarting ChibiOS\r\n");
  PRINT("Built at " __DATE__ " and exactly " __TIME__ "\r\n");

  thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                              "shell", NORMALPRIO + 1,
                                              shellThread, (void *)&shell_cfg1);
                                              
  /* Waiting termination.             */
  /*FIXME chThdWait(shelltp); */
  /*
   * Normal main() thread activity, spawning shells.
   */
  while (true) {
    /* Debugging the RTC Timer stuff */
    palWritePad(GPIOA, 5, PAL_LOW);
    gptStart(&GPTD4, &gpt4cfg);
    gptPolledDelay(&GPTD4, 78);
    palWritePad(GPIOA, 5, PAL_HIGH);
    gptStart(&GPTD4, &gpt4cfg);
    gptPolledDelay(&GPTD4, 78);
  }
}
