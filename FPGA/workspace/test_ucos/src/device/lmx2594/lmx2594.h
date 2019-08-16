#ifndef  __LMX2594_H
#define  __LMX2594_H

#include <stdint.h>

/// Structure to hold lmx2594 SPI settings
typedef struct {
	uint8_t chipSelectIndex;		///< valid 1~8
	uint8_t writeBitPolarity;		///< the level of the write bit of a SPI write instruction word, value is inverted for SPI read operation
	uint8_t longInstructionWord;	///< 1 = 16bit instruction word, 0 = 8bit instruction word
	uint8_t MSBFirst;				///< 1 = MSBFirst, 0 = LSBFirst
	uint8_t CPHA;					///< clock phase, sets which clock edge the data updates (valid 0 or 1)
	uint8_t CPOL;					///< clock polarity 0 = clock starts low, 1 = clock starts high
	uint8_t enSpiStreaming;			///< Not implemented. SW feature to improve SPI throughput.
	uint8_t autoIncAddrUp;			///< Not implemented. For SPI Streaming, set address increment direction. 1= next addr = addr+1, 0:addr = addr-1
	uint8_t fourWireMode;			///< 1: Use 4-wire SPI, 0: 3-wire SPI (SDIO pin is bidirectional). NOTE: ADI's FPGA platform always uses 4-wire mode.
	uint32_t spiClkFreq_Hz;			///< SPI Clk frequency in Hz (default 25000000), platform will use next lowest frequency that it's baud rate generator can create */
} lmx2594spiSettings_t;

/// Structure to hold AD9528 settings
typedef struct {
	struct gpio_desc *gpio_sync;
	struct gpio_desc *gpio_sysrefred;
	struct gpio_desc *gpio_muxout;
	struct spi_desc *spi_desc;
	lmx2594spiSettings_t  *spiSetting;
} lmx2594Device_t;


typedef enum {
	LMX2594_OK = 0,        /*!< HAL function successful. No error Detected */
	LMX2594_SPI_FAIL,      /*!< HAL SPI operation failure. SPI controller Down */
	LMX2594_GPIO_FAIL,     /*!< HAL GPIO function Failure */
	LMX2594_TIMER_FAIL,    /*!< HAL Timer function Failure */
	LMX2594_WAIT_TIMEOUT,  /*!< HAL function Timeout */
	LMX2594_GEN_SW,        /*!< HAL function failed due to general invalid  HAL data*/
	LMX2594_WARNING,       /*!< HAL function warning that non critical error was detected*/
	LMX2594_ERR
} lmx2594Err_t;

static lmx2594spiSettings_t lmx2594spisetting = {
		0, //chip select Index
		0, //Write bit polarity
		0, //8bit instruction word
		1, //MSB first
		0, //Clock phase
		0, //Clock polarity
		0, //uint8_t enSpiStreaming;
		1, //uint8_t autoIncAddrUp;
		1  //uint8_t fourWireMode;
};

lmx2594Err_t lmx2594_init(void);
lmx2594Err_t lmx2594_write(lmx2594Device_t *device, uint8_t addr, uint16_t data);



#endif
