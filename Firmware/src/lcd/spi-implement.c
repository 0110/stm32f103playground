/*
 * @file spi-implement.c
 *
 *  @date Nov 22, 2014
 *  @author c3ma
 */


#include "lcd/spi-implement.h"

#include "ch.h"
#include "hal.h"

/******************************************************************************
 * PROTOTYPE
 ******************************************************************************/

static void spicb(SPIDriver *spip);

/******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************/
/*
 * SPI configuration structure.
 * The slave select line is the pin GPIOA_SPI1NSS on the port GPIOA.
 */
static const SPIConfig spicfg = {
  spicb,
  /* HW dependent part.*/
  GPIOA,
  12,
  SPI_CR1_BR_2
};


/*
 * SPI end transfer callback.
 */
static void spicb(SPIDriver *spip)
{
  (void) spip;
}

/******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************/

spi_implement_ret_t spi_implement_init(void)
{

  /*
   * Initializes the first SPI driver. The SPI1 signals are routed as follow:
   * PA4 - NSS.
   * PA5 - SCK.
   * PA6 - MISO.
   * PA7 - MOSI.
   */
  spiStart(&SPID1, &spicfg);
  palSetPad(GPIOA, GPIOA_SPI1_NSS);
  palSetPadMode(GPIOA, GPIOA_SPI1_NSS, PAL_MODE_OUTPUT_PUSHPULL);        /* NSS.     */
  palSetPadMode(GPIOA, GPIOA_SPI1_SCK, PAL_MODE_OUTPUT_OPENDRAIN);           /* SCK.     */
  palSetPadMode(GPIOA, GPIOA_SPI1_MISO, PAL_MODE_INPUT);           /* MISO.    */
  palSetPadMode(GPIOA, GPIOA_SPI1_MOSI, PAL_MODE_OUTPUT_OPENDRAIN);           /* MOSI.    */

   return SPI_IMPL_RET_OK;
}

spi_implement_ret_t     spi_implement_send(int n, const void *txbuf)
{
  spiStartSendI(&SPID1, n, txbuf);
  return SPI_IMPL_RET_OK;
}
