/**
  @page STM32F401_Discovery Demo STM32F401_Discovery Demo
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    Demonstration/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description STM32F401 Discovery Demo description.
  ******************************************************************************
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

- Connect the STM32F401C-DISCO board to a PC with a 'USB type A to Mini-B' cable
through USB connector CN1 to power the board. Then red led LD1 (COM) and
LD2 (PWR) light up.
- All 4 leds between B1 and B2 are blinking as chenillard.
- Press User Button B1 (User) then MEMS sensor (LSM303DLHC) is enabled, move the
board and observe the four Leds blinking according to the motion direction.
- Connect the board to a PC with a second USB'type A to micro-B cable through USB 
connector CN5, this convert it to a standard mouse. Move the STM32F401C-DISCO 
board and see the mouse moves according to the motion direction.
- Press B1 or B2 to restart demonstration.

@par Directory contents 

  - Demonstration/stm32f4xx_conf.h     Library Configuration file
  - Demonstration/stm32f4xx_it.c       Interrupt handlers
  - Demonstration/stm32f4xx_it.h       Header for stm32f4xx_it.c
  - Demonstration/main.c               Main program
  - Demonstration/main.h               Header for main.c
  - Demonstration/system_stm32f4xx.c   STM32F4x system source file
  - Demonstration/usb_bsp.c            USB Board support package and is configurable by user.
  - Demonstration/usb_conf.h           USB General low level driver configuration
  - Demonstration/usbd_conf.h          USB Device configuration file
  - Demonstration/usbd_desc.c          USBD descriptors and string formating method
  - Demonstration/usbd_desc.h          Header for usbd_desc.c
  - Demonstration/usbc_usr.h           File includes the user application layer
                           

@par Hardware and Software environment

  - This Demo runs on STM32F401C Devices.
  
  - This example has been tested with STMicroelectronics STM32F401C-DISCO (MB1115B) 
    and can be easily tailored to any other supported device and development board.

  - STM32F401C-DISCO Set-up
    - None.
      
@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the STM32F401-Discovery_Demo.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
 
 + MDK-ARM
    - Open the Template.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5) 
    
 + TrueSTUDO
    - Open the TrueSTUDIO toolchain
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace directory
    - Click on File->Import, select General->'Existing Projects into Workspace' and then click "Next" 
    - Browse to the TrueSTUDIO workspace directory, select the project STM32F401C-DISCO
    - Rebuild all project files: Select the project in the "Project explorer" 
    window then click on Project->build project menu
    - Run program: Run->Debug (F11)
      
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
