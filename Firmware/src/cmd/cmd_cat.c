/*
 * cmd_cat.c
 *
 *  Created on: 25.06.2017
 *      Author: ollo
 */

#include "cmd/cmd.h"

#ifdef CMD_HAS_CAT

#include "ch.h"
#include "chprintf.h"
#include "ff.h"

void cmd_cat(BaseSequentialStream *chp, int argc, char *argv[]) {
	FIL fp;
	uint8_t buffer[32];
	int br;

	if (argc < 1) {
		chprintf(chp, "Usage: cmd <file to read>\r\n");
		return;
	}

	if (f_open(&fp, (TCHAR*) *argv, FA_READ) != FR_OK) {
		chprintf(chp, "[Cat Error] Failed to read file.\r\n");
		return;
	}

	do {
		if (f_read(&fp, (TCHAR*) buffer, 32, (UINT*) &br) != FR_OK) {
			chprintf(chp, "[Cat Error] Failed to read data\r\n");
			return;
		}

		chSequentialStreamWrite(chp, buffer, br);
	} while (!f_eof(&fp));

	f_close(&fp);

	chprintf(chp, "\r\n");
}

#endif
