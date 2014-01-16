/**
  @page FW_upgrade_Binary   Description of the "Upgrading STM32F401-DISCO board firmware using a USB key" application's binary files

  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    FW_upgrade/Binary/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the "Upgrading STM32F401 DISCOVERY board firmware using a USB key"
  *          application's binary files.
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

@par Description

Binary images of the user program
=================================
This folder contains the following images that can be loaded and executed by the 
FW upgrade application:  
    - STM32F401-Discovery_IOToggle_0x08008000.bin
    - STM32F401-Discovery_L3GD20_MEMS_0x08008000.bin

You have to load these binaries to the root directory of a USB key, then rename 
the binary to be executed to "image.bin".


After loading the program into  internal flash, the green LED (LED4) will be ON
indicating that the image.bin is well download into the flash. Push the user
button to start one of the examples below:
1- IOToggle Example: Is an example showing how to toggle LEDs mounted on STM32F401-DISCO
                     board.
2- L3GD20 MEMS example: Is an example showing how to configure and use for a specific
                        application (toggle LEDs in this example) the MEMS gyroscope 

Please refer to AN3990 which contains an overview of the firmware upgrade process 
and demonstrates how to run the firmware upgrade for STM32F4 discovery. the same 
process is used for STM32F401 discovery.
 
@par Hardware and Software environment  

  - This example runs on STM32F401x Devices.
    
  - This example has been tested with STMicroelectronics STM32F401-DISCO (MB1115B) 
    discovery boards and can be easily tailored to any other supported device and 
    development board.

 
@par How to use it ?
In order to make the program work, you must do the following :

 + EWARM
    - Open the STM32F401-Discovery_FW_Upgrade.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
    
 + MDK-ARM
    - Open the STM32F401-Discovery_FW_Upgrade.uvproj project
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

For more information, please refer to the document "Upgrading STM32F4DISCOVERY board
 firmware using a USB key (AN3990)" available on www.st.com/stm32f4-discovery. 
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
