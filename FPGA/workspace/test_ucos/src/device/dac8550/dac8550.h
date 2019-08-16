#ifndef  __DAC8550_H
#define  __DAC8550_H

/// Structure to hold AD9528 SPI settings
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
} dac8550spiSettings_t;

/// Structure to hold AD9528 settings
typedef struct {
//	struct gpio_desc *gpio_sync;
	struct spi_desc *spi_desc;
	dac8550spiSettings_t  *spiSetting;
} dac8550Device_t;


typedef enum {
	DAC8550_OK = 0,        /*!< HAL function successful. No error Detected */
	DAC8550_SPI_FAIL,      /*!< HAL SPI operation failure. SPI controller Down */
	DAC8550_GPIO_FAIL,     /*!< HAL GPIO function Failure */
	DAC8550_TIMER_FAIL,    /*!< HAL Timer function Failure */
	DAC8550_WAIT_TIMEOUT,  /*!< HAL function Timeout */
	DAC8550_GEN_SW,        /*!< HAL function failed due to general invalid  HAL data*/
	DAC8550_WARNING,       /*!< HAL function warning that non critical error was detected*/
	DAC8550_ERR
} dac8550Err_t;


static dac8550spiSettings_t dac8550spisetting = {
		0, //chip select Index
		0, //Write bit polarity
		1, //16bit instruction word
		1, //MSB first
		1, //Clock phase
		0, //Clock polarity
		0, //uint8_t enSpiStreaming;
		1, //uint8_t autoIncAddrUp;
		1  //uint8_t fourWireMode;
};

uint16 dac8550_cpl_d_value(uint16 mv);
dac8550Err_t dac8550_init(void);
dac8550Err_t dac8550_write(dac8550Device_t *device, uint8 pd, uint16 data);

#endif

