/**
  @page TIM_PWM_Output TIM PWM Output example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    TIM_PWM_Output/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the TIM PWM_Output example.
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

This example shows how to configure the TIM peripheral in PWM (Pulse Width Modulation) 
mode.

The TIM3CLK frequency is set to SystemCoreClock / 2 (Hz), to get TIM3 counter
clock at 14 MHz the Prescaler is computed as following:
   - Prescaler = (TIM3CLK / TIM3 counter clock) - 1

SystemCoreClock is set to 84 MHz for STM32F401xCxx Devices.

The TIM3 is running at 30 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
                                              = 14 MHz / 466 = 30 KHz
The TIM3 CCR1 register value is equal to 232, so the TIM3 Channel 1 generates a 
PWM signal with a frequency equal to 30 KHz and a duty cycle equal to 50%:
TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR + 1)* 100 = 50%

The TIM3 CCR2 register value is equal to 174, so the TIM3 Channel 2 generates a 
PWM signal with a frequency equal to 30 KHz and a duty cycle equal to 37.5%:
TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR + 1)* 100 = 37.5%

The TIM3 CCR3 register value is equal to 116, so the TIM3 Channel 3 generates a 
PWM signal with a frequency equal to 30 KHz and a duty cycle equal to 25%:
TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR + 1)* 100 = 25%

The TIM3 CCR4 register value is equal to 58, so the TIM3 Channel 4 generates a 
PWM signal with a frequency equal to 30 KHz and a duty cycle equal to 12.5%:
TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR + 1)* 100 = 12.5%

The PWM waveform can be displayed using an oscilloscope.


@par Directory contents 
  
  - TIM_PWM_Output/stm32f4xx_conf.h     Library Configuration file
  - TIM_PWM_Output/stm32f4xx_it.c       Interrupt handlers
  - TIM_PWM_Output/stm32f4xx_it.h       Interrupt handlers header file
  - TIM_PWM_Output/main.c               Main program 
  - TIM_PWM_Output/system_stm32f4xx.c   STM32F4xx system clock configuration file
  
 

@par Hardware and Software environment 

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board.    

  - STM32F401C-DISCO
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
        - PC.06: (TIM3_CH1)
        - PC.07: (TIM3_CH2)
        - PB.00: (TIM3_CH3)
        - PB.01: (TIM3_CH4)  

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the TIM_PWM_Output.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the TIM_PWM_Output.uvproj project
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
