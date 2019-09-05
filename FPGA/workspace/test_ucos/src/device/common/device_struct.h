
#ifndef __DEVICE_SRTUCT_H
#define __DEVICE_SRTUCT_H

typedef void * DeviceGpios;
typedef void * DevicePrivateCfg;

typedef enum {
	DEVICE_OK = 0,        /*!< HAL function successful. No error Detected */
	DEVICE_SPI_FAIL,      /*!< HAL SPI operation failure. SPI controller Down */
	DEVICE_GPIO_FAIL,     /*!< HAL GPIO function Failure */
	DEVICE_TIMER_FAIL,    /*!< HAL Timer function Failure */
	DEVICE_WAIT_TIMEOUT,  /*!< HAL function Timeout */
	DEVICE_GEN_SW,        /*!< HAL function failed due to general invalid  HAL data*/
	DEVICE_WARNING,       /*!< HAL function warning that non critical error was detected*/
	DEVICE_ERR
} DeviceErr_t;

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
} SpiSetting_t;

typedef struct {
	struct spi_desc *spi_desc;
	SpiSetting_t   *spiSetting;
	adiHalErr_t (*spiWriteData)(Device_t , uint16_t, uint8_t *);
	adiHalErr_t (*spiReadData)(Device_t , uint16_t, uint8_t *);
}DeviceSpi_t;

typedef struct {
	char	    		 deviceName[16];
	DeviceGpios    		 *gpio;              ///device gpio info pointer
	DeviceSpi_t     	 *spi;               ///device spi info
	DevicePrivateCfg     *DevicePrivCfg      ///device Private config
	uint32_t 			 _desired_time_to_elapse_10ms;
} Device_t;

#endif