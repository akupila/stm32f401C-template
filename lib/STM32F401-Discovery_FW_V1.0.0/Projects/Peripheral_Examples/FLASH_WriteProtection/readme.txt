/**
  @page FLASH_Write_Protection FLASH_Write_Protection
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    FLASH_Write_Protection/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the FLASH Write Protection example.
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

This example provides a description of how to enable and disable the write protection
for the STM32F401x FLASH.

By maintaining the User push-button pressed at Reset, the program will check the 
write protection status of FLASH_WRP_SECTORS (defined in main.c) 
  - If FLASH_WRP_SECTORS are write protected, the write protection will be disabled.
    Then LED4 will turn ON, if the protection disable operation is done correctly,
    otherwise LED5 turns ON.
  - If FLASH_WRP_SECTORS are not write protected, the write protection will be enabled.
    Then LED6 will turn ON, if the protection enable operation is done correctly,
    otherwise LED5 turns ON.

If after reset the User push-button is not pressed, the program will simply turn ON LED3. 


@par Directory contents 

  - FLASH_Write_Protection/system_stm32f4xx.c   STM32F4xx system clock configuration file
  - FLASH_Write_Protection/stm32f4xx_conf.h     Library Configuration file
  - FLASH_Write_Protection/stm32f4xx_it.c       Interrupt handlers
  - FLASH_Write_Protection/stm32f4xx_it.h       Header for stm32f4xx_it.c
  - FLASH_Write_Protection/main.c               Main program

  
      
@par Hardware and Software environment

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board

  - STM32F401C-DISCO  
    - Use LED4, LED3, LED5 and LED6 connected respectively to PD.12, PD.13, PD.14
      and PD.15 pins
    - Use the User push-button connected to pin PA0 (EXTI Line0)
    
      
@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the Flash_Write_Protection.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
    
+ MDK-ARM
    - Open the Flash_Write_Protection.uvproj project
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
