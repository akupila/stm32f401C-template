/**
  ******************************************************************************
  * @file    PWR_STANDBY/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief  This example shows how to enters the system to STANDBY mode and
  *         wake-up from this mode
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f401_discovery.h"

/** @addtogroup STM32F401_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup PWR_STANDBY
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef RTC_TimeStructure;

/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
static void SysTick_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f401xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */     

  /* Initialize LEDs and user-push Button mounted on STM32F401C-DISCO board */
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
      
  /* RTC configuration */
  RTC_Config();

  /* Turn on LED4 */
  STM_EVAL_LEDOn(LED4);

  /* Enable WKUP pin  */
  PWR_WakeUpPinCmd(ENABLE);

  /* Configure the SysTick to generate an interrupt each 250 ms */
  SysTick_Configuration();

  while (1)
  {
  }
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
  RTC_InitTypeDef RTC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Clear Wakeup flag */
  PWR_ClearFlag(PWR_FLAG_WU);

  /* Check if the StandBy flag is set */
  if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
  {
    /* Clear StandBy flag */
    PWR_ClearFlag(PWR_FLAG_SB);

    /* Wait for RTC APB registers synchronisation (needed after start-up from Reset)*/
    RTC_WaitForSynchro();
    /* No need to configure the RTC as the RTC config(clock source, enable,
       prescaler,...) are kept after wake-up from STANDBY */
  }
  else
  {
    /* RTC Configuration ******************************************************/
    /* Reset Backup Domain */
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

/* The RTC Clock may varies due to LSI frequency dispersion. */   
    /* Enable the LSI OSC */ 
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */  
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation (needed after start-up from Reset)*/
    RTC_WaitForSynchro();

    /* Set the RTC time base to 1s */
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv = 0x00FF;

    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
      /* Turn on LED3 */
      STM_EVAL_LEDOn(LED3);
      
      /* User can add here some code to deal with this error */
      while(1);
    }

    /* Set the time to 01h 00mn 00s AM */
    RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours   = 0x01;
    RTC_TimeStructure.RTC_Minutes = 0x00;
    RTC_TimeStructure.RTC_Seconds = 0x00;  
  
    if(RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure) == ERROR)
    {
      /* Turn on LED3 */
      STM_EVAL_LEDOn(LED3);
      
      /* User can add here some code to deal with this error */
      while(1);
    }
  }

  /* Clear RTC Alarm Flag */ 
  RTC_ClearFlag(RTC_FLAG_ALRAF);
}

/**
  * @brief  Configures the SysTick to generate an interrupt each 250 ms.
  * @param  None
  * @retval None
  */
static void SysTick_Configuration(void)
{
  /* SysTick interrupt each 250 ms */
  if (SysTick_Config((SystemCoreClock/8) / 4))
  { 
    /* Capture error */ 
    while (1);
  }

  /* Select AHB clock(HCLK) divided by 8 as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

  /* Set SysTick Preemption Priority to 1 */
  NVIC_SetPriority(SysTick_IRQn, 0x04);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
