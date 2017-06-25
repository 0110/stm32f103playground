/*
 * cmd.h
 *
 *  Created on: 25.06.2017
 *      Author: ollo
 */

#ifndef SRC_CMD_CMD_H_
#define SRC_CMD_CMD_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define CMD_HAS_CAT

#ifdef CMD_HAS_CAT
void cmd_cat(BaseSequentialStream *chp, int argc, char *argv[]);
#endif


#endif /* SRC_CMD_CMD_H_ */
