/**
  @page RCC_Example RCC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    RCC_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the RCC example.
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

This example shows how to use, for debug purpose, the RCC_GetClocksFreq function 
to retrieve the current status and frequencies of different on chip clocks. 
You can see the RCC_ClockFreq structure content, which hold the frequencies of 
different on chip clocks, using your toolchain debugger.

This example handles also the High Speed External clock (HSE) failure detection:
when the HSE clock disappears (broken or disconnected external Quartz); HSE, PLL
are disabled (but no change on PLL config), HSI selected as system clock source
and an interrupt (NMI) is generated. In the NMI ISR, the HSE, HSE ready interrupt
are enabled and once HSE clock recover, the HSERDY interrupt is generated and in
the RCC ISR routine the system clock is reconfigured to its previous state (before
HSE clock failure). You can monitor the system clock on MCO2 pin(PC9).

Four LEDs are toggled with a timing defined by the Delay function.

@par Directory contents 

  - RCC_Example/system_stm32f4xx.c   STM32F4xx system clock configuration file 
  - RCC_Example/stm32f4xx_conf.h     Library Configuration file
  - RCC_Example/stm32f4xx_it.c       Interrupt handlers
  - RCC_Example/stm32f4xx_it.h       Interrupt handlers header file
  - RCC_Example/main.c               Main program
 
@par Hardware and Software environment

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board

  - STM32F401C-DISCO
    - LED4, LED3, LED5 and LED6 connected respectively to PD.12, PD.13, PD.14
      and PD.15 pins.
    - Connect the PC9 pin to an oscilloscope to monitor the system clock frequency.
      	       
@par How to use it ?

In order to make the program work, you must do the following :

 + EWARM
    - Open the RCC_Example.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the RCC_Example.uvproj project
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
