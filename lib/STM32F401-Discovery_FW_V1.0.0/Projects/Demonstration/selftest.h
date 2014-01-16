/**
  ******************************************************************************
  * @file    selftest.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Header for selftest.c module
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SELFTEST_H
#define __SELFTEST_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Audio_Test(void);
void LSM303DLHC_MEMS_Test(void);
void L3GD20_MEMS_Test(void);
void USB_Test(void);
void Microphone_MEMS_Test(void);
void Demo_GyroConfig(void);
void LSM303DLHC_CompassReadAcc(float* pfData);

#endif /* __SELFTEST_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
