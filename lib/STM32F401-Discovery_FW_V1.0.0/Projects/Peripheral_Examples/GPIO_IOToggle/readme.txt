/**
  @page GPIO_IOToggle GPIO IO Toggle example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    GPIO_IOToggle/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the GPIO IO Toggle example.
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

This example describes how to toggle the GPIO pins connected on AHB bus.

PD12, PD13, PD14 and PD15 (configured in output pushpull mode) toggles in a forever loop.
 - Set PD12, PD13, PD14 and PD15 by setting corresponding bits in BSRRL register
 - Reset PD12, PD13, PD14 and PD15  by setting corresponding bits in BSRRH register

In this example, HCLK is configured at 84 MHz.

@par Directory contents 

  - IO_Toggle/stm32f4xx_conf.h    Library Configuration file
  - IO_Toggle/stm32f4xx_it.c      Interrupt handlers
  - IO_Toggle/stm32f4xx_it.h      Interrupt handlers header file
  - IO_Toggle/main.c              Main program
  - IO_Toggle/system_stm32f4xx.c  STM32F4xx system source file

@par Hardware and Software environment

  - This example runs on STM32F401xCxx Devices.

  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board

  - STM32F401C-DISCO
    - LED4, LED3, LED5 and LED6 are connected respectively to PD.12, PD.13, PD.14 and PD.15.
      

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the GPIO_IOToggle.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
    
+ MDK-ARM
    - Open the GPIO_IOToggle.uvproj project
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
