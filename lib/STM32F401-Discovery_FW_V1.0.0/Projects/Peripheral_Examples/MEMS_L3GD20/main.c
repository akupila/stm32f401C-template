/**
  ******************************************************************************
  * @file    MEMS_L3GD20/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   This example shows how to configure the MEMS gyroscope 
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
#include "main.h"

/** @addtogroup STM32F401_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup MEMS_L3GD20
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define ABS(x)                    (x < 0) ? (-x) : x
#define L3G_Sensitivity_250dps    (float)114.285f        /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_500dps    (float)57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_2000dps   (float)14.285f         /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
  
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void MEMS_Test(void);
static void Demo_GyroConfig(void);
static void Demo_GyroReadAngRate (float* pfData);

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  files (startup_stm32f401xx.s) before to branch to application main. 
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f4xx.c file
  */  
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
     
  /* Infinite loop */
  while (1)
  {
    MEMS_Test();
  }
}
/**
* @brief  Mems gyroscope application.
* @param  None
* @retval None
*/
static void MEMS_Test(void)
{
  float Buffer[6];
  uint8_t Xval, Yval = 0x00;
  
  /* Demo Gyroscope */
  Demo_GyroConfig();
  
  /* Read Gyro Angular data */
  Demo_GyroReadAngRate(Buffer);
  
  /* Update autoreload and capture compare registers value*/
  Xval = ABS((int8_t)(Buffer[0]));
  Yval = ABS((int8_t)(Buffer[1])); 
  
  if ( Xval>Yval)
  {
    if ((int8_t)Buffer[0] > 15.0f)
    {       
      STM_EVAL_LEDOn(LED4);
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED5);
      STM_EVAL_LEDOff(LED6);
    }
    if ((int8_t)Buffer[0] < -15.0f)
    {
      STM_EVAL_LEDOn(LED5);
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED6);
    }
  }
  else
  {
    if ((int8_t)Buffer[1] < -15.0f)
    {
      STM_EVAL_LEDOn(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED5);
      STM_EVAL_LEDOff(LED6);
    }
    if ((int8_t)Buffer[1] > 15.0f)
    {
      STM_EVAL_LEDOn(LED6);
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOff(LED4);
      STM_EVAL_LEDOff(LED5);
    } 
  } 
}

/**
* @brief  Configure the Mems to gyroscope application.
* @param  None
* @retval None
*/
static void Demo_GyroConfig(void)
{
  L3GD20_InitTypeDef L3GD20_InitStructure;
  L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;
  /* Configure Mems L3GD20 */
  L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
  L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1;
  L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
  L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4;
  L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
  L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
  L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500; 
  L3GD20_Init(&L3GD20_InitStructure);
  
  L3GD20_FilterStructure.HighPassFilter_Mode_Selection =L3GD20_HPM_NORMAL_MODE_RES;
  L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;
  L3GD20_FilterConfig(&L3GD20_FilterStructure) ;
  
  L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);
}

/**
* @brief  Calculate the angular Data rate Gyroscope.
* @param  pfData : Data out pointer
* @retval None
*/
void Demo_GyroReadAngRate (float* pfData)
{
  uint8_t tmpbuffer[6] ={0};
  int16_t RawData[3] = {0};
  uint8_t tmpreg = 0;
  float sensitivity = 0;
  uint32_t wCounter =0;
  
  L3GD20_Read(&tmpreg,L3GD20_CTRL_REG4_ADDR,1);
  
  L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);
  
  /* check in the control register 4 the data alignment (Big Endian or Little Endian)*/
  if(!(tmpreg & 0x40))
  {
    for(wCounter=0; wCounter<3; wCounter++)
    {
      RawData[wCounter]=(int16_t)(((uint16_t)tmpbuffer[2*wCounter+1] << 8) + tmpbuffer[2*wCounter]);
    }
  }
  else
  {
    for(wCounter=0; wCounter<3; wCounter++)
    {
      RawData[wCounter]=(int16_t)(((uint16_t)tmpbuffer[2*wCounter] << 8) + tmpbuffer[2*wCounter+1]);
    }
  }
  
  /* Switch the sensitivity value set in the CRTL4 */
  switch(tmpreg & 0x30)
  {
  case 0x00:
    sensitivity=L3G_Sensitivity_250dps;
    break;
    
  case 0x10:
    sensitivity=L3G_Sensitivity_500dps;
    break;
    
  case 0x20:
    sensitivity=L3G_Sensitivity_2000dps;
    break;
  }
  /* divide by sensitivity */
  for(wCounter=0; wCounter<3; wCounter++)
  {
    pfData[wCounter]=(float)RawData[wCounter]/sensitivity;
  }
}

/**
* @brief  Basic management of the timeout situation.
* @param  None.
* @retval None.
*/
uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
  return 0;
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
