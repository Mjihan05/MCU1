/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "Reg_Macros.h"
#include "RCC.h"
#include "Intc.h"
#include "Gpio.h"
#include "Dio.h"
#include "Spi.h"
#include "string.h"

/** Pin Definition SPI 1
 * PA4 - SPI1_NSS
 * PA5 - SPI1_SCK
 * PA6 - SPI1_MISO
 * PA7 - SPI1_MOSI
 * */

/** Pin Definition SPI 2
 * PB12 - SPI2_NSS
 * PB13 - SPI2_SCK
 * PB14 - SPI2_MISO
 * PB15 - SPI2_MOSI
 * */

/** Arduino Defines */
#define NACK 0xA5
#define ACK 0xF5
//command codes
#define COMMAND_LED_CTRL          0x50
#define COMMAND_SENSOR_READ       0x51
#define COMMAND_LED_READ          0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ         0x54

//#define ONE_CHANNEL_USED

/********************************* Test Code ******************************************************/

#define ISR_SPI_1_GLOBAL 	(35U)
#define ISR_SPI_2_GLOBAL 	(36U)

#define SEQUENCE_0 (0U)
#define SEQUENCE_1 (1U)
#define SEQUENCE_2 (2U)
#define SEQUENCE_3 (3U)

#define SEQUENCE_COMMAND_LED_CTRL (0U)
#define SEQUENCE_COMMAND_SENSOR_READ (0U)
#define SEQUENCE_COMMAND_PRINT (0U)
#define SEQUENCE_ID_READ (0U)

#define CHANNEL_0 (0U)
#define CHANNEL_1 (1U)
#define CHANNEL_2 (2U)
#define CHANNEL_LENGTH (6U)

#define DUMMY_DATA 				(0xFF)
#define UNO_BUILTIN_LED 		(13U)
#define CHANNEL_CMD_LED_CTRL	(0U)
#define CHANNEL_RX_ACK			(1U)
#define CHANNEL_PIN_VALUE		(2U)

#define CHANNEL_CMD_SENSOR_READ	(0U)
#define ANALOG_PIN_0   			(14U)

#define CHANNEL_CMD_PRINT 	(0U)
#define CHANNEL_PRINT_DATA 	(1U)

#define CHANNEL_CMD_ID_READ (0U)
#define CHANNEL_READ_DATA 	(1U)

#define CHECK_RETURN_VALUE(x)  while(x)


uint8_t sampleTxDataCh1[CHANNEL_LENGTH] = {0xA,0xC,0xD,0xE,0xF};
//char data[] = "Hello World";
uint8_t  sampleTxDataCh2[CHANNEL_LENGTH] = {0x5,0xB,0xC,0xD,0xE,0xF};

uint8_t ledCtrl_TxData[] = {COMMAND_LED_CTRL,DUMMY_DATA,UNO_BUILTIN_LED,STD_HIGH};
uint8_t ledCtrl_RxData[4];

uint8_t sensorRead_TxData[] = {COMMAND_SENSOR_READ,DUMMY_DATA,ANALOG_PIN_0,DUMMY_DATA};
uint8_t sensorRead_RxData[4];

uint8_t printData[] = "Hello World";
uint8_t print_TxData[] = {COMMAND_PRINT,DUMMY_DATA,11U};
uint8_t print_RxData[3];

uint8_t idRead_TxData[] = {COMMAND_ID_READ,DUMMY_DATA};
uint8_t idRead_RxCMD[2];
uint8_t idRead_RxData[10U];

uint8_t myName[] = "Michael Jihan";


Spi_DataBufferType sampleRxDataCh1[CHANNEL_LENGTH];
Spi_DataBufferType sampleRxDataCh2[CHANNEL_LENGTH];

void delay()
{
	for(uint32_t j =0; j<2; j++)
	{
		for(uint32_t i =0; i<500000;)
			{
			i++;
			}
	}

}

int main(void)
{
	Std_ReturnType returnValue = E_NOT_OK;

	RCC_Init(&RCC_Config0);
	Port_Init (&Port_Config0);

	Spi_Init(&Spi_Config0);

	NVIC_EnableIRQ(ISR_SPI_1_GLOBAL);
	NVIC_EnableIRQ(ISR_SPI_2_GLOBAL);
	Spi_SetAsyncMode(SPI_POLLING_MODE);


	//returnValue = Spi_DeInit();

	//returnValue = Spi_WriteIB (CHANNEL_0,(Spi_DataBufferType*)sampleTxDataCh1);
	//CHECK_RETURN_VALUE(returnValue);

	//returnValue = Spi_SetupEB (CHANNEL_1,(Spi_DataBufferType*)sampleTxDataCh2,(Spi_DataBufferType*)&sampleRxDataCh2,CHANNEL_LENGTH);
	//CHECK_RETURN_VALUE(returnValue);

#if 0
	while(1)
	{
		if(Dio_ReadChannel(GPIO_A_PIN_0) == 0x1U)
		{
			Spi_WriteIB (CHANNEL_0,(Spi_DataBufferType*)sampleTxDataCh1);
			Spi_SetupEB (CHANNEL_1,(Spi_DataBufferType*)sampleTxDataCh2,(Spi_DataBufferType*)&sampleRxDataCh2,6U);
			returnValue =  Spi_SyncTransmit(SEQUENCE_0);
			CHECK_RETURN_VALUE(returnValue);
			delay();
		}
		else
		{

		}
	}
#endif


#if 0
	while(1)
	{
		if(Dio_ReadChannel(GPIO_A_PIN_0) == 0x1U)
		{
#ifdef ONE_CHANNEL_USED
			/** COMMAND_LED_CTRL */
			//Spi_WriteIB (CHANNEL_CMD_LED_CTRL,(Spi_DataBufferType*)(ledCtrl_TxData+0U));
			Spi_SetupEB(CHANNEL_CMD_LED_CTRL,(Spi_DataBufferType*)ledCtrl_TxData,(Spi_DataBufferType*)&ledCtrl_RxData,4U);
			returnValue =  Spi_SyncTransmit(SEQUENCE_COMMAND_LED_CTRL);
			CHECK_RETURN_VALUE(returnValue);
			//Spi_ReadIB (CHANNEL_CMD_LED_CTRL,(Spi_DataBufferType*)ledCtrl_RxData);
			CHECK_RETURN_VALUE((ledCtrl_RxData[1] != ACK));
			delay();

			/** COMMAND_SENSOR_READ */
			while(Dio_ReadChannel(GPIO_A_PIN_0) != 0x1U);
			Spi_SetupEB(CHANNEL_CMD_SENSOR_READ,(Spi_DataBufferType*)sensorRead_TxData,(Spi_DataBufferType*)sensorRead_RxData,4U);
			returnValue =  Spi_SyncTransmit(SEQUENCE_COMMAND_LED_CTRL);
			CHECK_RETURN_VALUE(returnValue);
			CHECK_RETURN_VALUE((sensorRead_RxData[1] != ACK));
#else
			/** COMMAND_PRINT  Make modification in pbcfg enable channel 1 */
			while(Dio_ReadChannel(GPIO_A_PIN_0) != 0x1U);
			Spi_SetupEB(CHANNEL_CMD_PRINT,(Spi_DataBufferType*)print_TxData,print_RxData,3U);
			Spi_SetupEB(CHANNEL_PRINT_DATA,(Spi_DataBufferType*)printData,NULL_PTR,strlen(printData));
			returnValue =  Spi_SyncTransmit(SEQUENCE_COMMAND_PRINT);
			CHECK_RETURN_VALUE(returnValue);
			//CHECK_RETURN_VALUE((print_RxData[1] != ACK));
			delay();

			/** COMMAND_ID_READ  Make modification in pbcfg enable channel 1 */
			while(Dio_ReadChannel(GPIO_A_PIN_0) != 0x1U);
			Spi_SetupEB(CHANNEL_CMD_ID_READ,(Spi_DataBufferType*)idRead_TxData,idRead_RxCMD,2U);
			Spi_SetupEB(CHANNEL_READ_DATA,(Spi_DataBufferType*)NULL_PTR,idRead_RxData,10U);
			returnValue =  Spi_SyncTransmit(SEQUENCE_ID_READ);
			//Spi_ReadIB (CHANNEL_READ_DATA,(Spi_DataBufferType*)idRead_RxData);
			CHECK_RETURN_VALUE(returnValue);
			//CHECK_RETURN_VALUE((print_RxData[1] != ACK));
			delay();
#endif


			while(1);


		}
		else
		{

		}
	}

#endif

#if 0
	while(1)
	{
		if(Dio_ReadChannel(GPIO_A_PIN_0) == 0x1U)
		{
			Spi_SetupEB(CHANNEL_CMD_PRINT,(Spi_DataBufferType*)print_TxData,print_RxData,3U);
			Spi_SetupEB(CHANNEL_PRINT_DATA,(Spi_DataBufferType*)printData,NULL_PTR,strlen(printData));

			returnValue =  Spi_AsyncTransmit (SEQUENCE_1);
			CHECK_RETURN_VALUE(returnValue);

			returnValue =  Spi_AsyncTransmit (SEQUENCE_COMMAND_PRINT);
			CHECK_RETURN_VALUE(returnValue);

			returnValue =  Spi_AsyncTransmit (SEQUENCE_2);
			if(returnValue == E_NOT_OK)
			{
				Spi_Cancel(SEQUENCE_1);
			}

			returnValue =  Spi_AsyncTransmit (SEQUENCE_COMMAND_PRINT);
			CHECK_RETURN_VALUE(!returnValue);

			returnValue =  Spi_AsyncTransmit (SEQUENCE_3);
			CHECK_RETURN_VALUE(!returnValue);

			delay();
			Spi_MainFunction_Handling();
		}
	}
#endif

#if 1
	while(1)
	{
		if(Dio_ReadChannel(GPIO_A_PIN_0) == 0x1U)
		{
			Spi_SetupEB(CHANNEL_CMD_PRINT,(Spi_DataBufferType*)print_TxData,print_RxData,3U);
			Spi_SetupEB(CHANNEL_PRINT_DATA,(Spi_DataBufferType*)printData,NULL_PTR,strlen(printData));

			Spi_SetupEB(CHANNEL_2,(Spi_DataBufferType*)myName,NULL_PTR,strlen(myName));
			//Spi_WriteIB (CHANNEL_2,(Spi_DataBufferType*)myName);

			returnValue =  Spi_AsyncTransmit (SEQUENCE_COMMAND_PRINT);
			CHECK_RETURN_VALUE(returnValue);

			returnValue =  Spi_AsyncTransmit (SEQUENCE_1);
			CHECK_RETURN_VALUE(returnValue);

			delay();
			Spi_MainFunction_Handling();
		}
	}
#endif

	for(;;);
}
