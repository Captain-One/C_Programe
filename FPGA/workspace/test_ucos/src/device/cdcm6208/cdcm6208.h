#ifndef  __CDCM6208_H
#define  __CDCM6208_H

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
} cdcm6208spiSettings_t;

/// Structure to hold AD9528 settings
typedef struct {
	struct gpio_desc *gpio_resetb;
	struct gpio_desc *gpio_ref_sel;
	struct spi_desc *spi_desc;
	cdcm6208spiSettings_t  *spiSetting;
} cdcm6208Device_t;


typedef enum {
	CDCM6208_OK = 0,        /*!< HAL function successful. No error Detected */
	CDCM6208_SPI_FAIL,      /*!< HAL SPI operation failure. SPI controller Down */
	CDCM6208_GPIO_FAIL,     /*!< HAL GPIO function Failure */
	CDCM6208_TIMER_FAIL,    /*!< HAL Timer function Failure */
	CDCM6208_WAIT_TIMEOUT,  /*!< HAL function Timeout */
	CDCM6208_GEN_SW,        /*!< HAL function failed due to general invalid  HAL data*/
	CDCM6208_WARNING,       /*!< HAL function warning that non critical error was detected*/
	CDCM6208_ERR
} cdcm6208Err_t;

static cdcm6208spiSettings_t cdcm6208spisetting = {
		0, //chip select Index
		0, //Write bit polarity
		1, //16bit instruction word
		1, //MSB first
		0, //Clock phase
		0, //Clock polarity
		0, //uint8_t enSpiStreaming;
		1, //uint8_t autoIncAddrUp;
		1  //uint8_t fourWireMode;
};

cdcm6208Err_t cdcm6208_init(void);
cdcm6208Err_t cdcm6208_write(cdcm6208Device_t *device, uint16 addr, uint16 data);
cdcm6208Err_t cdcm6208_read(cdcm6208Device_t *device, uint16 addr, uint16 *readdata);
cdcm6208Err_t cdcm6208_setTimeout_ms(uint32_t timeOut_ms);
cdcm6208Err_t cdcm6208_hasTimeoutExpired(void);


#endif
