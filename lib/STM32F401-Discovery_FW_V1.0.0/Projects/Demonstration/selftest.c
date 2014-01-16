/**
  ******************************************************************************
  * @file    selftest.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   This file provides the hardware tests
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
#include "selftest.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MEMS_PASSCONDITION              5

#define L3G_Sensitivity_250dps     (float)   114.285f         /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps] */
#define L3G_Sensitivity_500dps     (float)    57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps] */
#define L3G_Sensitivity_2000dps    (float)    14.285f	      /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
#define PI                         (float)     3.14159265f

#define LSM_Acc_Sensitivity_2g     (float)     1.0f            /*!< accelerometer sensitivity with 2 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_4g     (float)     0.5f            /*!< accelerometer sensitivity with 4 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_8g     (float)     0.25f           /*!< accelerometer sensitivity with 8 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_16g    (float)     0.0834f         /*!< accelerometer sensitivity with 12 g full scale [LSB/mg] */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Init Structure definition */
RCC_ClocksTypeDef      RCC_Clocks;
ADC_InitTypeDef        ADC_InitStructure;
ADC_CommonInitTypeDef  ADC_CommonInitStructure;

__IO uint16_t ConvData1, ConvData2;
__IO uint16_t counter0 = 0, counter1 = 0, Idx = 0;
uint8_t ADC_Channel[2] = {ADC_Channel_2, ADC_Channel_3};
uint8_t GPIO_Pin [2] = {GPIO_Pin_2, GPIO_Pin_3};

uint16_t count = 0, count1 = 24, Left_Right = 0;
const int16_t sinebuf[48] = {0, 4276, 8480, 12539, 16383, 19947, 23169, 25995,
                             28377, 30272, 31650, 32486, 32767, 32486, 31650, 30272,
                             28377, 25995, 23169, 19947, 16383, 12539, 8480, 4276,
                             0, -4276, -8480, -12539, -16383, -19947, -23169, -25995,
                             -28377, -30272, -31650, -32486, -32767, -32486, -31650, -30272,
                             -28377, -25995, -23169, -19947, -16383, -12539, -8480, -4276
                             };

extern __IO uint32_t TimingDelay;
extern __IO int8_t X_Offset, Y_Offset, Z_Offset;
float pBuffer[6];
extern uint8_t Buffer[6];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief Test LSM303DLHC MEMS Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   MEMS peripheral.
  * @param None
  * @retval None
  */
void LSM303DLHC_MEMS_Test(void)
{
  LSM303DLHCAcc_InitTypeDef LSM303DLHCAcc_InitStructure;
  LSM303DLHCAcc_FilterConfigTypeDef LSM303DLHCFilter_InitStructure;
  
  uint8_t memsteststatus = 0x00;
  uint8_t xdata = 0, ydata = 0;
  
  /* MEMS configuration ------------------------------------------------------*/
   /* Fill the accelerometer structure */
  LSM303DLHCAcc_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
  LSM303DLHCAcc_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
  LSM303DLHCAcc_InitStructure.Axes_Enable= LSM303DLHC_AXES_ENABLE;
  LSM303DLHCAcc_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
  LSM303DLHCAcc_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
  LSM303DLHCAcc_InitStructure.Endianness=LSM303DLHC_BLE_LSB;
  LSM303DLHCAcc_InitStructure.High_Resolution=LSM303DLHC_HR_ENABLE;
  /* Configure the accelerometer main parameters */
  LSM303DLHC_AccInit(&LSM303DLHCAcc_InitStructure);
  
  /* Fill the accelerometer LPF structure */
  LSM303DLHCFilter_InitStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
  LSM303DLHCFilter_InitStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
  LSM303DLHCFilter_InitStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
  LSM303DLHCFilter_InitStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;

  /* Configure the accelerometer LPF main parameters */
  LSM303DLHC_AccFilterConfig(&LSM303DLHCFilter_InitStructure);

  /* Required delay for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
                                                             = 3/100 = 30ms */
  Delay(30);
  
  TimingDelay = 500;
  /* Wait until detecting all MEMS direction or timeout */
  while((memsteststatus == 0x00)&&(TimingDelay != 0x00))
  {
    LSM303DLHC_CompassReadAcc(pBuffer);
    xdata = ABS((int8_t)(pBuffer[0]));
    ydata = ABS((int8_t)(pBuffer[2]));
    /* Check test PASS condition */   
    if ((xdata > MEMS_PASSCONDITION) || (ydata > MEMS_PASSCONDITION)) 
    {
      /* MEMS Test PASS */
      memsteststatus = 0x01;
    }
  }
  
  /* MEMS test status: PASS */ 
  if(memsteststatus != 0x00)
  {
    /* Turn Green LED ON: signaling MEMS Test PASS */
    STM_EVAL_LEDOn(LED4);
    
    /* Waiting User Button is pressed */
    while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET)
    {}
    
    /* Waiting User Button is Released */
    while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET)
    {}
    
    /* Turn Green LED OFF: signaling the end of MEMS Test and switching to 
       the next Sub Test */
    STM_EVAL_LEDOff(LED4);
  }
  /* MEMS test status: Timeout occurs */
  else
  {
    Fail_Handler();
  }
}

/**
  * @brief Test L3GD20 MEMS Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   MEMS peripheral.
  * @param None
  * @retval None
  */
void L3GD20_MEMS_Test(void)
{
  uint8_t temp, memsteststatus = 0x00;
  uint8_t ptemp[1] = {0xA5};
    
  /* MEMS configuration ------------------------------------------------------*/
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
  
  
  L3GD20_Write(ptemp, L3GD20_CTRL_REG1_ADDR, 1);
  
  L3GD20_Read(&temp, L3GD20_CTRL_REG1_ADDR, 1);
  
  /* Required delay for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
  = 3/100 = 30ms */
  Delay(30);
  
  /* Read WHO_AM_I register */
  L3GD20_Read(&temp, L3GD20_WHO_AM_I_ADDR, 1);
  
  /* Check device identification register, this register should contains 
  the device identifier that for LSM303DLHC is set to 0x3B */
  if (temp != I_AM_L3GD20)
  {
    Fail_Handler();
  }
  else
  {
    /* MEMS Test PASS */
    memsteststatus = 0x01;
  }
    
  /* MEMS test status: PASS */ 
  if(memsteststatus != 0x00)
  {
    /* Turn Green LED ON: signaling MEMS Test PASS */
    STM_EVAL_LEDOn(LED4);
    
    /* Waiting User Button is pressed */
    while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET)
    {}
    
    /* Waiting User Button is Released */
    while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET)
    {}
    
    /* Turn Green LED OFF: signaling the end of MEMS Test and switching to 
    the next Sub Test */
    STM_EVAL_LEDOff(LED4);
  }
  /* MEMS test status: Timeout occurs */
  else
  {
    Fail_Handler();
  }
}

/**
  * @brief Test USB Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   Audio and USB peripheral.
  * @param None
  * @retval None
  */
void USB_Test(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /******************************** USB Test **********************************/
  
  /*----------------- Part1: without cables connected ------------------------*/ 
  
  /* GPIOA, GPIOC and GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | \
                         RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* GPIOD Configuration: Pins 5 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  /* Turn LED8 ON using PD5 */
  GPIO_ResetBits(GPIOD, GPIO_Pin_5);
  
  /* GPIOC Configuration: Pin 0 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 ON using PC0 (5v) */
  GPIO_ResetBits(GPIOC, GPIO_Pin_0); 
  
  /* Waiting delay 10ms */
  Delay(1);
  
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 10 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check the ID level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_RESET)
  {
    Fail_Handler();
  }
  
  /* Turn LED7 OFF using PC0 */
  GPIO_SetBits(GPIOC, GPIO_Pin_0);  
  
  /* GPIOA Configuration: Pins 11, 12 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA11 and PA12 level without cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET) || \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 12 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 11 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_11);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA12 level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET)
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 11 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 12 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA12 level without cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET)
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 ON using PA9 */
  GPIO_SetBits(GPIOA, GPIO_Pin_9);
  
  /* Turn Green LED ON: signaling Audio USB Test part1 PASS */
  STM_EVAL_LEDOn(LED4);

  /* GPIOA Configuration: Pins 9, 10, 11 and 12 in input pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  /* Waiting User Button is pressed */
  while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET)
  {}
  
  /* Waiting User Button is Released */
  while (STM_EVAL_PBGetState(BUTTON_USER) != Bit_RESET)
  {}
  
  /* Turn Green LED OFF: signaling the end of Audio USB Test part1 and switching to 
  the part2 */
  STM_EVAL_LEDOff(LED4);
  
  /* Turn LED7 OFF using PA9 */
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
  
  /* Turn LED8 OFF using PD5 */
  GPIO_SetBits(GPIOD, GPIO_Pin_5);
  
  /*--------------- Part2: with Audio USB cables connected  ------------------*/ 
  
  /*********************************** USB Test *******************************/
  /* Check the ID level with cable connected */
  if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) != Bit_RESET)
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 11, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_9);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA11 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET) || \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 11 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_11);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA9 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)|| \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == Bit_RESET))
  {
    Fail_Handler();
  }
  
  /* GPIOA Configuration: Pins 9, 11 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 12 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_12);
  
  /* Waiting delay 10ms */
  Delay(1);
  
  /* Check PA9 and PA12 level with cable connected */
  if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == Bit_RESET)|| \
      (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == Bit_RESET))
  {
    Fail_Handler();
  }

  /* GPIOA Configuration: Pins 11, 12 in input pull-down */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Pin 9 in output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Turn LED7 OFF using PA9 */
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
}

/**
  * @brief Test Audio Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   Audio peripheral.
  * @param  None
  * @retval None
  */
void Audio_Test(void)
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;  
  uint8_t audioteststatus = 0x00;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Set the current audio interface: I2S or DAC */
  EVAL_AUDIO_SetAudioInterface();
  
  /* Initialize the Audio codec and all related peripherals (I2S, I2C, IOs...) */
  /* I2S code to be exectued under the I2S interrupt */
  if (EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 87, I2S_AudioFreq_48k) !=0)
  {
    Fail_Handler();
  }

  /* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles; 
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  /* ADC peripherals Init */
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* Configure ADC Channels pin as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  counter1 = 0;
  counter0 = 0;
  audioteststatus = 0;
 
  /* Set Injected sequencer length */
  ADC_InjectedSequencerLengthConfig(ADC1, 2);
  /* ADCperipheral[PerIdx] Injected Channel Config */ 
  ADC_InjectedChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_56Cycles);
  ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_56Cycles);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
 
  TimingDelay = 500;
  /* Wait until detecting 500 data*/
  while((audioteststatus == 0)&&(TimingDelay != 0))
  {
    /* ADC1 injected Software Start Conv */ 
    ADC_SoftwareStartInjectedConv(ADC1);
    
    ConvData1 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
    ConvData2 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
    
    /* 1.75V equals to 150 */
    if ((ConvData1 > 150) && (ConvData2 < 10) && (counter1 != 500))
    {
      counter1 ++;
    }
    if ((ConvData1 < 10) && (ConvData2 > 150) && (counter0 != 500))
    {
      counter0 ++;
    }
    if((counter1 == 500) && (counter0 == 500))
    {
      audioteststatus = 1; 
    }
  }
  
  /* Disable ADC Peripherals */ 
  ADC_Cmd(ADC1, DISABLE);
  
  /* Audio test status: FAIL */ 
  if(audioteststatus == 0x00)
  {
    Fail_Handler();
  }
  
  /* Turn Green LED ON: signaling Audio USB Test part2 PASS */
  STM_EVAL_LEDOn(LED4);
  
  /* Waiting User_Button pressed */
  while (STM_EVAL_PBGetState(BUTTON_USER) == Bit_RESET)
  {}
  
  /* Turn Green LED OFF: signaling the end of Audio USB Test part2 */
  STM_EVAL_LEDOff(LED4);
}

/**
  * @brief Test Micophone MEMS Hardware.
  *   The main objectif of this test is to check the hardware connection of the 
  *   Microphone MEMS peripheral.
  * @param None
  * @retval None
  */
void Microphone_MEMS_Test(void)
{
  uint16_t data = 0x00;
  uint8_t index = 0x00;
  I2S_InitTypeDef  I2S_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable the SPI clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(SPI_SCK_GPIO_CLK | SPI_MOSI_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
  GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(SPI_SCK_GPIO_PORT, SPI_SCK_SOURCE, SPI_SCK_AF);
  
  /* SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPI_MOSI_PIN;
  GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT, SPI_MOSI_SOURCE, SPI_MOSI_AF);
  
  /* I2S configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI2);
  I2S_InitStructure.I2S_AudioFreq = 64000;
  I2S_InitStructure.I2S_Standard = I2S_Standard_MSB;
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
  I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;
  I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  /* Initialize the I2S peripheral with the structure above */
  I2S_Init(SPI2, &I2S_InitStructure);
  
  /* Enable the I2S peripheral */
  I2S_Cmd(SPI2, ENABLE);
  
  /* Waiting until MEMS microphone ready : Wake-up Time */
  Delay(10);
  
  TimingDelay = 500;
  /* Wait until detect the click on the MEMS microphone or TimeOut delay*/
  while((index < 30) && (TimingDelay != 0x00))
  { 
    /* Waiting RXNE Flag or TimeOut delay */
    while((SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET)&& (TimingDelay != 0x00))
    {}
    data = SPI_I2S_ReceiveData(SPI2);
    if (data == 0xFFFF)
    {
      index++;  
    }
  }
  
  /* MEMS microphone test status: Timeout occurs */
  if(index != 30)
  {
    Fail_Handler();
  }
}

/**
* @brief  Configure the Mems to gyroscope application.
* @param  None
* @retval None
*/
void Demo_GyroConfig(void)
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
* @brief Read LSM303DLHC output register, and calculate the acceleration ACC=(1/SENSITIVITY)* (out_h*256+out_l)/16 (12 bit rappresentation)
* @param pnData: pointer to float buffer where to store data
* @retval None
*/
void LSM303DLHC_CompassReadAcc(float* pfData)
{
  int16_t pnRawData[3];
  uint8_t ctrlx[2];
  uint8_t buffer[6], cDivider;
  uint8_t i = 0;
  float LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_2g;
  
  /* Read the register content */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, 2, ctrlx);
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A, 6, buffer);
  
  if(ctrlx[1]&0x40)
    cDivider=64;
  else
    cDivider=16;
  
  /* check in the control register4 the data alignment*/
  if(!(ctrlx[0] & 0x40) || (ctrlx[1] & 0x40)) /* Little Endian Mode or FIFO mode */
  {
    for(i=0; i<3; i++)
    {
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/cDivider;
    }
  }
  else /* Big Endian Mode */
  {
    for(i=0; i<3; i++)
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1])/cDivider;
  }
  /* Read the register content */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, 2, ctrlx);
  
  
  if(ctrlx[1]&0x40)
  {
    /* FIFO mode */
    LSM_Acc_Sensitivity = 0.25;
  }
  else
  {
    /* normal mode */
    /* switch the sensitivity value set in the CRTL4*/
    switch(ctrlx[0] & 0x30)
    {
    case LSM303DLHC_FULLSCALE_2G:
      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_2g;
      break;
    case LSM303DLHC_FULLSCALE_4G:
      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_4g;
      break;
    case LSM303DLHC_FULLSCALE_8G:
      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_8g;
      break;
    case LSM303DLHC_FULLSCALE_16G:
      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_16g;
      break;
    }
  }
  
  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    pfData[i]=(float)pnRawData[i]/LSM_Acc_Sensitivity;
  }
}

/*--------------------------------
       Callbacks implementation:
           the callbacks prototypes are defined in the stm324xg_eval_audio_codec.h file
           and their implementation should be done in the user code if they are needed.
           Below some examples of callback implementations.
                                     --------------------------------------------------------*/
/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* Calculate the remaining audio data in the file and the new size 
     for the DMA transfer. If the Audio files size is less than the DMA max 
     data transfer size, so there is no calculation to be done, just restart 
     from the beginning of the file ... */
  /* Check if the end of file has been reached */

}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void EVAL_AUDIO_HalfTransfer_CallBack(uint32_t pBuffer, uint32_t Size)
{  
#ifdef AUDIO_MAL_MODE_CIRCULAR
  
  /* Display message on the LCD screen */
  LCD_DisplayStringLine(Line8, " 1/2 Buffer Reached "); 
  
#endif /* AUDIO_MAL_MODE_CIRCULAR */
  
  /* Generally this interrupt routine is used to load the buffer when 
  a streaming scheme is used: When first Half buffer is already transferred load 
  the new data to the first half of buffer while DMA is transferring data from 
  the second half. And when Transfer complete occurs, load the second half of 
  the buffer while the DMA is transferring from the first half ... */
  /* 
    ...........
                   */
}
/**
  * @brief  Get next data sample callback
  * @param  None
  * @retval Next data sample to be sent
  */
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  uint16_t data = 0;

  if (Left_Right==0)
  {
    /* Get the next sample to be sent */
    data = sinebuf[count++];
    
    if (count == 48)
    {
      count = 0x00;
    }
    Left_Right = 1;
  }
  else
  {
    /* Get the next sample to be sent */
    data = sinebuf[count1++];
    
    if (count1 == 48)
    {
      count1 = 0x00;
    }
    Left_Right = 0;
  }
  return data;
}

/**
  * @brief  Manages the DMA FIFO error interrupt.
  * @param  None
  * @retval None
  */
void EVAL_AUDIO_Error_CallBack(void* pData)
{
  /* Stop the program with an infinite loop */
  while (1)
  {}
  
  /* could also generate a system reset to recover from the error */
  /* .... */
}

#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t Codec_TIMEOUT_UserCallback(void)
{   
  /* Block communication and all processes */
  while (1)
  {   
  }
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */
/*----------------------------------------------------------------------------*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
