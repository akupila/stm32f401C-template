/**
  @page TIM_PWM_Input TIM PWM Input example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    TIM_PWM_Input/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the TIM PWM_Input example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
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
   @endverbatim

@par Example Description 

This example shows how to use the TIM peripheral to measure the frequency and 
duty cycle of an external signal.

The TIMxCLK frequency is set to SystemCoreClock/4 (Hz), the Prescaler is 0 so the 
counter clock is SystemCoreClock/2 (Hz).
SystemCoreClock is set to 84 MHz fro STM32F401xCxx Devices.

TIM4 is configured in PWM Input Mode: the external signal is connected to 
TIM4 Channel2 used as input pin.
To measure the frequency and the duty cycle we use the TIM4 CC2 interrupt request,
so In the TIM4_IRQHandler routine, the frequency and the duty cycle of the external 
signal are computed. 
The "Frequency" variable contains the external signal frequency:
TIM4 counter clock = SystemCoreClock / 2,
Frequency = TIM4 counter clock / TIM4_CCR2 in Hz, 
The "DutyCycle" variable contains the external signal duty cycle:
DutyCycle = (TIM4_CCR1*100)/(TIM4_CCR2) in %.

The minimum frequency value to measure is 1280 Hz (TIM4 counter clock / CCR MAX). 

@par Directory contents 

  - TIM_PWM_Input/stm32f4xx_conf.h     Library Configuration file
  - TIM_PWM_Input/stm32f4xx_it.c       Interrupt handlers
  - TIM_PWM_Input/stm32f4xx_it.h       Interrupt handlers header file
  - TIM_PWM_Input/main.c               Main program 
  - TIM_PWM_Input/system_stm32f4xx.c   STM32F4xx system clock configuration file

 

@par Hardware and Software environment 

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board.   

  - STM32F401C-DISCO
    - Connect the external signal to measure to the TIM4 CH2 pin (PB.07).

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the TIM_PWM_Input.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the TIM_PWM_Input.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)
  
 + TrueSTUDO
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace directory.
    - Click on File->Import, select General->'Existing Projects into Workspace' and then click "Next". 
    - Browse to the TrueSTUDIO workspace directory, select the project.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Run->Debug (F11)
            
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
