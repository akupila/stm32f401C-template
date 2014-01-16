/**
  ******************************************************************************
  * @file    PWR_CurrentConsumption/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   This example shows how to configure the STM32F4xx system to measure different
  *          Low Power modes current consumption
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
#include "stm32f4xx_lp_modes.h"

/** @addtogroup STM32F401_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t UserButtonStatus = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  __IO uint32_t counter = 0;
  
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f401xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */
  
  /* Enable PWR APB1 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to Backup */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset RTC Domain */
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

  /* Configure User Button */
  STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_EXTI);
  
  /* Wait until User button is pressed to enter the Low Power mode */
  while(UserButtonStatus == 0x00)
  { 
  }
  /* Loop while User button is maintained pressed */
  while(STM_EVAL_PBGetState(BUTTON_USER) != RESET)
  {
  }

#if defined (SLEEP_MODE)
  /* Sleep Mode Entry 
      - System Running at PLL (84MHz)
      - Flash 3 wait state
      - Prefetch and Cache enabled
      - Code running from Internal FLASH
      - All peripherals disabled.
      - Wakeup using EXTI Line (User Button PA.00)
   */
  SleepMode_Measure();
#elif defined (STOP_MODE)
  /* STOP Mode Entry 
      - RTC Clocked by LSI
      - Regulator in LP mode
      - HSI, HSE OFF and LSI OFF if not used as RTC Clock source  
      - No IWDG
      - FLASH in deep power down mode
      - Automatic Wakeup using RTC clocked by LSI (after ~20s)
   */
  StopMode_Measure();
#elif defined (STANDBY_MODE)
  /* STANDBY Mode Entry 
      - Backup SRAM and RTC OFF
      - IWDG and LSI OFF
      - Wakeup using WakeUp Pin (PA.00)
   */
  StandbyMode_Measure();
#elif defined (STANDBY_RTC_MODE)
  /* STANDBY Mode with RTC on LSI Entry 
      - RTC Clocked by LSI
      - IWDG OFF and LSI OFF if not used as RTC Clock source
      - Backup SRAM OFF
      - Automatic Wakeup using RTC clocked by LSI (after ~20s)
   */

  StandbyRTCMode_Measure();
#elif defined (STANDBY_RTC_BKPSRAM_MODE)
  /* STANDBY Mode with RTC on LSI Entry 
      - RTC Clocked by LSI
      - Backup SRAM ON
      - IWDG OFF
      - Automatic Wakeup using RTC clocked by LSI (after ~20s)
  */
  
  StandbyRTCBKPSRAMMode_Measure();
#else

  /* Initialize LED4 on STM32F401C-DISCO board */
  STM_EVAL_LEDInit(LED4);
  
  /* Infinite loop */
  while (1)
  {
    /* Toggle The LED4 */
    STM_EVAL_LEDToggle(LED4);

    /* Inserted Delay */
    for(counter = 0; counter < 0x5FF; counter++);
  }
#endif

  /* Infinite loop */
  while (1)
  {
  }  
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
