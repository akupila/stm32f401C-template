/**
  @page DMA_FLASHToRAM DMA FLASH to RAM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    DMA_FLASHToRAM/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   Description of the DMA FLASH to RAM example.
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

This example provides a description of how to use a DMA channel to transfer 
a word data buffer from FLASH memory to embedded SRAM memory.

DMA2 Stream0 channel0 is configured to transfer the contents of a 32-word data 
buffer stored in Flash memory to the reception buffer declared in RAM.

The start of transfer is triggered by software. DMA2 Stream0 channel0 memory-to-memory
transfer is enabled. Source and destination addresses incrementing is also enabled.
The transfer is started by setting the Channel enable bit for DMA2 Stream0 channel0.
At the end of the transfer a Transfer Complete interrupt is generated since it
is enabled. The Transfer Complete Interrupt pending bit is then cleared. 
When the DMA transfer is completed the DMA Stream is disabled by hardware.
The main application can check on the Stream Enable status to detect the end of
transfer or can also check on the number of remaining transfers which should be 
equal to 0 at the end of the transfer. 
A comparison between the source and destination buffers is done to check that all 
data have been correctly transferred.

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED4 is ON when the program starts.
 - LED3 is ON when the configuration phase is done and the transfer is started.
 - LED5 is ON when the transfer is complete (into the Transfer Complete interrupt
   routine)
 - LED6 is ON when the comparison result between source buffer and destination 
   buffer is passed.

It is possible to select a different Stream and/or channel for the DMA transfer
example by modifying defines values in the file main.h.
Note that only DMA2 Streams are able to perform Memory-to-Memory transfers.

There are different options to check on the DMA end of transfer:
 1. Use DMA Transfer Complete interrupt.
 2. Use DMA enable state (the DMA stream is disabled by hardware when transfer 
    is complete).
 3. Use DMA Stream transfer counter value (the counter value is decremented when
    transfer is ongoing and is equal to 0 at the transfer end).
 4. Use DMA Transfer Complete flag (polling mode).

In this example methods 1, 2 and 3 are provided (you can select between method 2 
and 3 by uncommenting relative code in waiting loop in the main.c file).


@par Directory contents 

  - DMA_FLASHToRAM/system_stm32f40x.c   STM32F4xx system clock configuration file
  - DMA_FLASHToRAM/stm32f4xx_conf.h     Library Configuration file
  - DMA_FLASHToRAM/stm32f4xx_it.c       Interrupt handlers
  - DMA_FLASHToRAM/stm32f4xx_it.h       Interrupt handlers header file
  - DMA_FLASHToRAM/main.c               Main program
  - DMA_FLASHToRAM/main.h               Main program header file

      
@par Hardware and Software environment

  - This example runs on STM32F401xCxx Devices.
  
  - This example has been tested with STM32F401C-DISCO (MB1115) RevB and can be
    easily tailored to any other development board.
    

@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the DMA_FLASHToRAM.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

+ MDK-ARM
    - Open the DMA_FLASHToRAM.uvproj project
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
