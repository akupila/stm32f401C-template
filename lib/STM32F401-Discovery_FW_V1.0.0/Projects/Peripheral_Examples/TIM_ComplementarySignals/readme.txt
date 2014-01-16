/**
  @page TIM_ComplementarySignals TIM Complementary Signals example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    TIM_ComplementarySignals/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the TIM Complementary Signals example.
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

This example shows how to configure the TIM1 peripheral to generate three 
complementary TIM1 signals, to insert a defined dead time value, to use the break 
feature and to lock the desired parameters.

TIM1CLK is fixed to SystemCoreClock, the TIM1 Prescaler is equal to 0 so the 
TIM1 counter clock used is SystemCoreClock (84 MHz).

The objective is to generate PWM signal at 17.57 KHz:
  - TIM1_Period = (SystemCoreClock / 17570) - 1

The Three Duty cycles are computed as the following description: 
The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
The Timer pulse is calculated as follows:
  - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

A dead time equal to 11/SystemCoreClock is inserted between the different 
complementary signals, and the Lock level 1 is selected.
The break Polarity is used at High level.

The TIM1 waveform can be displayed using an oscilloscope.


@par Directory contents 

  - TIM_ComplementarySignals/stm32f4xx_conf.h    Library Configuration file
  - TIM_ComplementarySignals/stm32f4xx_it.c      Interrupt handlers
  - TIM_ComplementarySignals/stm32f4xx_it.h      Interrupt handlers header file
  - TIM_ComplementarySignals/main.c              Main program
  - TIM_ComplementarySignals/system_stm32f4xx.c  STM32F4xx system source file

  
@par Hardware and Software environment 

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board.
    
  - STM32F401C-DISCO
    - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:
      - TIM1_CH1  pin (PA.08)  
      - TIM1_CH1N pin (PB.13)  
      - TIM1_CH2  pin (PE.11)  
      - TIM1_CH2N pin (PB.14)  
      - TIM1_CH3  pin (PA.10)  
      - TIM1_CH3N pin (PB.15)

    - Connect the TIM1 break pin TIM1_BKIN pin (PB.12) to the GND. To generate a 
      break event, switch this pin level from 0V to 3.3V.  


@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the TIM_ComplementarySignals.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the TIM_ComplementarySignals.uvproj project
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
