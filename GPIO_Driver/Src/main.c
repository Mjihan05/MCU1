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

#include <stdint.h>
#include "Reg_Macros.h"
#include "RCC.h"
#include "Gpio.h"
#include "Dio.h"
#include "NVIC_regTypes.h"

#define BUTTON_LED_TOGGLE
//#define API_TEST


void delay (void)
{
	uint32_t i = 0;
	for(i=0;i<500000; i++);
}

int main(void)
{
				/** GPIO/DIO Test Application  */
#ifdef API_TEST
	//RCC_AHB1PeripheralClkEnable(EN_GPIOA);
	Port_Init (&Port_Config0);

#if(GPIO_PORT_LOCK == STD_ON)
	GPIO_A.MODER.B.ModeR1 = 0x1U; /** should not change*/
	GPIO_Port_Unlock(0U);
//	GPIO_A.MODER.B.ModeR1 = 0x1U; /** should change*/
#else
	Port_SetPinDirection(GPIO_A_PIN_1,PORT_PIN_OUT);
	Port_RefreshPortDirection();
	Port_SetPinMode(GPIO_A_PIN_1,PIN_MODE_ANALOG);
	Port_SetPinMode(GPIO_A_PIN_1,PIN_MODE_ALT_FUNC_8);
	Port_SetPinMode(GPIO_A_PIN_1,PIN_MODE_GPIO);
#endif

	uint8_t u8_result = Dio_ReadChannel (GPIO_B_PIN_6);
	Dio_WriteChannel (GPIO_B_PIN_6,(~u8_result)&0x1);
	u8_result = Dio_ReadChannel (GPIO_B_PIN_6);

	u8_result = Dio_FlipChannel (GPIO_B_PIN_6);
	u8_result = Dio_FlipChannel (GPIO_B_PIN_6);
	u8_result = Dio_FlipChannel (GPIO_B_PIN_4);

	Dio_MaskedWritePort (0U,0xAAAA,0x00FF);
	Dio_MaskedWritePort (1U,0xAAAA,0x0FF0);


	Dio_ConfigPortMasks();
	uint16_t u16_result = Dio_ReadPort (1U);
	Dio_WritePort (1U,~u16_result);

	Dio_WriteChannelGroup(&Dio_ChannelGroup[0U],0x2);
	u16_result = Dio_ReadChannelGroup (&Dio_ChannelGroup[0U]);

	Dio_WriteChannelGroup(&Dio_ChannelGroup[1U],0x4);
	u16_result = Dio_ReadChannelGroup (&Dio_ChannelGroup[1U]);
#endif

	NVIC.ISER[0] = 0x1;
	//NVIC.ICER[0] = 0x1;
	NVIC.ISER[2] = 0x1;
	//NVIC.ICER[2] = 0x1;
	NVIC.ISPR[0] = 0x1;
	//NVIC.ISPR[2] = 0x1;
	//NVIC.ICPR[0] = 0x1;
	//NVIC.ICPR[2] = 0x1;
	//NVIC.IABR[0] = 0x1;
	//NVIC.IABR[2] = 0x1;
	NVIC.IPR[0] = 0x4<<4U;
	NVIC.IPR[1] = 0x4<<4U;
	NVIC.STIR.INTID = 0x1;

#ifdef BUTTON_LED_TOGGLE
	Port_Init (&Port_Config0);
	while(1)
	{
		if(Dio_ReadChannel(GPIO_A_PIN_0) == 0x1U)
		{
			Dio_FlipChannel (GPIO_D_PIN_12);
			delay();
		}
	}

#endif /** (BUTTON_LED_TOGGLE) */

#if 0
	RCC_AHB1PeripheralClkEnable(EN_GPIOD);
	GPIO_D.MODER.B.ModeR1 = 0x1U;
	GPIO_D.MODER.R = (0x1U<<2U);

	if((GPIO_B.MODER.B.ModeR1)==0x1U)
	{
		RCC_AHB1PeripheralClkEnable(EN_GPIOC);
	}
#endif
	for(;;);
}
