/**
  ******************************************************************************
  * @file    stm32f401_discovery_lsm303dlhc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   This file provides a set of functions needed to manage the lsm303dlhc
  *          MEMS accelerometer available on STM32F401-Discovery Kit.
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
/* Includes ------------------------------------------------------------------*/
#include "stm32f401_discovery_lsm303dlhc.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32F401_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32F401_DISCOVERY_LSM303DLHC
  * @{
  */


/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_Macros
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_Variables
  * @{
  */ 
__IO uint32_t  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
__IO uint16_t  LSM303DLHC_Address = 0;   
/**
  * @}
  */

/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_FunctionPrototypes
  * @{
  */
static void LSM303DLHC_LowLevel_Init(void);
/**
  * @}
  */

/** @defgroup STM32F401_DISCOVERY_LSM303DLHC_Private_Functions
  * @{
  */

/**
  * @brief  Set LSM303DLHC Initialization.
  * @param  LSM303DLHC_InitStruct: pointer to a LSM303DLHC_InitTypeDef structure 
  *         that contains the configuration setting for the LSM303DLHC.
  * @retval None
  */
void LSM303DLHC_AccInit(LSM303DLHCAcc_InitTypeDef *LSM303DLHC_InitStruct)
{  
  uint8_t ctrl1 = 0x00, ctrl4 = 0x00;
  
  /* Configure the low level interface ---------------------------------------*/
  LSM303DLHC_LowLevel_Init();
  
  /* Configure MEMS: data rate, power mode, full scale and axes */
  ctrl1 |= (uint8_t) (LSM303DLHC_InitStruct->Power_Mode | LSM303DLHC_InitStruct->AccOutput_DataRate | \
                    LSM303DLHC_InitStruct->Axes_Enable);
  
  ctrl4 |= (uint8_t) (LSM303DLHC_InitStruct->BlockData_Update | LSM303DLHC_InitStruct->Endianness | \
                    LSM303DLHC_InitStruct->AccFull_Scale|LSM303DLHC_InitStruct->High_Resolution);
                    
  /* Write value to ACC MEMS CTRL_REG1 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG1_A, 1, &ctrl1);
  
  /* Write value to ACC MEMS CTRL_REG4 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, 1, &ctrl4);
}

/**
  * @brief  Reboot memory content of LSM303DLHC
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccRebootCmd(void)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG5 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A, 1, &tmpreg);
  
  /* Enable or Disable the reboot memory */
  tmpreg |= LSM303DLHC_BOOT_REBOOTMEMORY;
  
  /* Write value to ACC MEMS CTRL_REG5 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A, 1, &tmpreg);
}

/**
  * @brief  Set High Pass Filter Modality
  * @param  LSM303DLHC_FilterStruct: pointer to a LSM303DLHC_FilterConfigTypeDef structure 
  *         that contains the configuration setting for the LSM303DLHC.        
  * @retval None
  */
void LSM303DLHC_AccFilterConfig(LSM303DLHCAcc_FilterConfigTypeDef *LSM303DLHC_FilterStruct) 
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG2 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
  
  tmpreg &= 0x0C;
  
  /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
  tmpreg |= (uint8_t) (LSM303DLHC_FilterStruct->HighPassFilter_Mode_Selection |\
                      LSM303DLHC_FilterStruct->HighPassFilter_CutOff_Frequency|\
                      LSM303DLHC_FilterStruct->HighPassFilter_AOI1|\
                      LSM303DLHC_FilterStruct->HighPassFilter_AOI2);                             
  
  /* Write value to ACC MEMS CTRL_REG2 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
}

/**
  * @brief  Enable or Disable High Pass Filter
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be: 
  *         @arg: LSM303DLHC_HighPassFilter_DISABLE 
  *         @arg: LSM303DLHC_HighPassFilter_ENABLE          
  * @retval None
  */
void LSM303DLHC_AccFilterCmd(uint8_t HighPassFilterState)
 {
  uint8_t tmpreg;
  
  /* Read CTRL_REG2 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
                  
  tmpreg &= 0xF7;

  tmpreg |= HighPassFilterState;

  /* Write value to ACC MEMS CTRL_REG2 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
}

/**
  * @brief  Enable or Disable High Pass Filter on CLick
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be: 
  *         @arg: LSM303DLHC_HighPassFilter_DISABLE 
  *         @arg: LSM303DLHC_HighPassFilter_ENABLE          
  * @retval None
  */
void LSM303DLHC_AccFilterClickCmd(uint8_t HighPassFilterClickState)
 {
  uint8_t tmpreg;
  
  /* Read CTRL_REG2 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
                  
  tmpreg &= 0xFB;

  tmpreg |= HighPassFilterClickState;

  /* Write value to ACC MEMS CTRL_REG2 regsister */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, 1, &tmpreg);
}

/**
  * @brief Set LSM303DLHC Interrupt1 configuration
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT1_CLICK
  *         @arg   LSM303DLHC_IT1_AOI1
  *         @arg   LSM303DLHC_IT1_AOI2
  *         @arg   LSM303DLHC_IT1_DRY1
  *         @arg   LSM303DLHC_IT1_WTM
  *         @arg   LSM303DLHC_IT1_OVERRUN              
  * @param  NewState: new state of the selected LSM303DLHC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LSM303DLHC_AccIT1Config(uint8_t LSM303DLHC_IT, FunctionalState NewState)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, 1, &tmpval);
    
  tmpval &= ~LSM303DLHC_IT;
  
  if (NewState != DISABLE)
  {
    tmpval |= LSM303DLHC_IT;
  }
  else
  {
    /* Disable the selected interrupt */
    tmpval =~ LSM303DLHC_IT;
  }
      
  /* Write value to MEMS CTRL_REG3 register */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, 1, &tmpval);  
}

/**
  * @brief Set LSM303DLHC Interrupt2 configuration
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT2_CLICK2
  *         @arg   LSM303DLHC_IT2_INT1
  *         @arg   LSM303DLHC_IT2_INT2
  *         @arg   LSM303DLHC_IT2_BOOT
  *         @arg   LSM303DLHC_IT2_ACT
  *         @arg   LSM303DLHC_IT2_HLACTIVE              
  * @param  NewState: new state of the selected LSM303DLHC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LSM303DLHC_AccIT2Config(uint8_t LSM303DLHC_IT, FunctionalState NewState)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, 1, &tmpval);
    
  tmpval &= ~LSM303DLHC_IT;
  
  if (NewState != DISABLE)
  {
    tmpval |= LSM303DLHC_IT;
  }
  else
  {
    /* Disable the selected interrupt */
    tmpval =~ LSM303DLHC_IT;
  }
      
  /* Write value to MEMS CTRL_REG3 register */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, 1, &tmpval);  
}

/**
  * @brief  INT1 interrupt config
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled 
  *         NewState: Enable or Disable    
  * @retval None
  */
void LSM303DLHC_AccINT1InterruptConfig(uint8_t ITCombination, uint8_t ITAxes, FunctionalState NewState )
{  
  uint8_t tmpval = ITCombination;
  
  /* Read INT1_CFR register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, 1, &tmpval);
  
  if (NewState != DISABLE)
  {
    tmpval |= ITAxes;
  }
  else
  {
    /* Disable the selected interrupt */
    tmpval =(~ITAxes)|ITCombination;
  }
      
  /* Write value to MEMS INT1_CFR register */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, 1, &tmpval);  
}

/**
  * @brief  INT1 interrupt config
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled 
  *         NewState: Enable or Disable    
  * @retval None
  */
void LSM303DLHC_AccINT2InterruptConfig(uint8_t ITCombination, uint8_t ITAxes, FunctionalState NewState )
{  
  uint8_t tmpval = ITCombination;
  
  /* Read INT2_CFR register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, 1, &tmpval);
  
  if (NewState != DISABLE)
  {
    tmpval |= ITAxes;
  }
  else
  {
    /* Disable the selected interrupt */
    tmpval =(~ITAxes)|ITCombination;
  }
      
  /* Write value to MEMS INT2_CFR register */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, 1, &tmpval);  
}

/**
  * @brief  INT1 interrupt config
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled 
  *         NewState: Enable or Disable    
  * @retval None
  */
void LSM303DLHC_AccClickITConfig(uint8_t ITClick, FunctionalState NewState)
{  
  uint8_t tmpval;
  
  /* Read CLICK_CFR register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, 1, &tmpval);
  
  if (NewState != DISABLE)
  {
    tmpval |= ITClick;
  }
  else
  {
    /* Disable the selected interrupt */
    tmpval =~ITClick;
  }
      
  /* Write value to MEMS CLICK_CFR register */
  LSM303DLHC_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, 1, &tmpval);  
}

/**
  * @brief  Get status for Acc LSM303DLHC data
  * @param  None         
  * @retval Data status in a LSM303DLHC Data register
  */
uint8_t LSM303DLHC_AccGetDataStatus(void)
{
  uint8_t tmpreg;
  
  /* Read Mag STATUS register */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_STATUS_REG_A, 1, &tmpreg);
                  
  return tmpreg;
}

/**
  * @brief  Set LSM303DLHC Mag Initialization.
  * @param  LSM303DLHC_InitStruct: pointer to a LSM303DLHC_MagInitTypeDef structure 
  *         that contains the configuration setting for the LSM303DLHC.
  * @retval None
  */
void LSM303DLHC_MagInit(LSM303DLHCMag_InitTypeDef *LSM303DLHC_InitStruct)
{  
  uint8_t cra_regm = 0x00, crb_regm = 0x00, mr_regm = 0x00;
  
  /* Configure the low level interface ---------------------------------------*/
  LSM303DLHC_LowLevel_Init();
  
  /* Configure MEMS: temp and Data rate */
  cra_regm |= (uint8_t) (LSM303DLHC_InitStruct->Temperature_Sensor | LSM303DLHC_InitStruct->MagOutput_DataRate);
    
  /* Configure MEMS: full Scale */
  crb_regm |= (uint8_t) (LSM303DLHC_InitStruct->MagFull_Scale);
      
  /* Configure MEMS: working mode */
  mr_regm |= (uint8_t) (LSM303DLHC_InitStruct->Working_Mode);
                    
  /* Write value to Mag MEMS CRA_REG regsister */
  LSM303DLHC_Write(MAG_I2C_ADDRESS, LSM303DLHC_CRA_REG_M, 1, &cra_regm);
  
  /* Write value to Mag MEMS CRB_REG regsister */
  LSM303DLHC_Write(MAG_I2C_ADDRESS, LSM303DLHC_CRB_REG_M, 1, &crb_regm);

  /* Write value to Mag MEMS MR_REG regsister */
  LSM303DLHC_Write(MAG_I2C_ADDRESS, LSM303DLHC_MR_REG_M, 1, &mr_regm);
}

/**
  * @brief  Get status for Mag LSM303DLHC data
  * @param  None         
  * @retval Data status in a LSM303DLHC Data register
  */
uint8_t LSM303DLHC_MagGetDataStatus(void)
{
  uint8_t tmpreg;
  
  /* Read Mag STATUS register */
  LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_SR_REG_M, 1, &tmpreg);
                  
  return tmpreg;
}

/**
  * @brief  Reads a block of data from the LSM303DLHC.
  * @param  DeviceAddr : specifies the slave address to be programmed(ACC_I2C_ADDRESS or MAG_I2C_ADDRESS).
  * @param  RegisterAddr : specifies the LSM303DLHC internal address register to read from.
  * @param  NumByteToRead : number of bytes to read from the LSM303DLH ( NumByteToRead >1  only for the Mgnetometer readinf).
  * @param  pBuffer : pointer to the buffer that receives the data read from the LSM303DLH.
  * @retval LSM303DLHC register value
  */
uint16_t LSM303DLHC_Read(uint8_t DeviceAddr, uint8_t RegisterAddr,
                              uint16_t NumByteToRead,
                              uint8_t* pBuffer)
{
  __IO uint32_t LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  __IO uint32_t temp;
  
  LSM303DLHC_I2C_Config();
  
restart:
  
  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
/* Send START condition */
  I2C_GenerateSTART(LSM303DLHC_I2C, ENABLE);
  /* Test on EV5 and clear it */
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if (LSM303DLHC_Timeout-- == 0)
      return ERROR;
  }
     
  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  /* Send slave address for read */
  I2C_Send7bitAddress(LSM303DLHC_I2C, DeviceAddr, I2C_Direction_Transmitter);
  
  while (!I2C_CheckEvent(LSM303DLHC_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if (LSM303DLHC_Timeout-- == 0)
    {
      I2C_ClearFlag(LSM303DLHC_I2C,I2C_FLAG_BUSY|I2C_FLAG_AF);
      goto restart;
    } 
  }
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(LSM303DLHC_I2C, ENABLE);

  I2C_SendData(LSM303DLHC_I2C, RegisterAddr);

  /* Test on EV8 and clear it */
  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if (LSM303DLHC_Timeout-- == 0)
     return ERROR;
  }
  
  if (NumByteToRead == 0x01)
  {
    restart3:  
    /* Send START condition */
    I2C_GenerateSTART(LSM303DLHC_I2C, ENABLE);
    while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send Slave address for read */
    I2C_Send7bitAddress(LSM303DLHC_I2C, DeviceAddr, I2C_Direction_Receiver);
    /* Wait until ADDR is set */
    LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
    while (!I2C_GetFlagStatus(LSM303DLHC_I2C, I2C_FLAG_ADDR))   
    {
      if (LSM303DLHC_Timeout-- == 0) 
      {
        I2C_ClearFlag(LSM303DLHC_I2C,I2C_FLAG_BUSY|I2C_FLAG_AF);
        goto restart3;
      }
    }
    /* Clear ACK */
    I2C_AcknowledgeConfig(LSM303DLHC_I2C, DISABLE);
    __disable_irq();
    /* Clear ADDR flag */
    temp = LSM303DLHC_I2C->SR2;
    /* Program the STOP */
    I2C_GenerateSTOP(LSM303DLHC_I2C, ENABLE);
    __enable_irq();
    while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x0040) != 0x000040); /* Poll on RxNE */
    /* Read the data */
    *pBuffer = I2C_ReceiveData(LSM303DLHC_I2C);
    /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
    while ((LSM303DLHC_I2C->CR1&0x200) == 0x200);
    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(LSM303DLHC_I2C, ENABLE);

    return SUCCESS;
  }
  else
    if(NumByteToRead == 0x02)
    {
      restart4:     
      /* Send START condition */
      I2C_GenerateSTART(LSM303DLHC_I2C, ENABLE);
      while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_MODE_SELECT));
      /* Send EEPROM address for read */
      I2C_Send7bitAddress(LSM303DLHC_I2C, DeviceAddr, I2C_Direction_Receiver);
      LSM303DLHC_I2C->CR1 = 0xC01; /* ACK=1; POS =1 */
      LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
      while (!I2C_GetFlagStatus(LSM303DLHC_I2C, I2C_FLAG_ADDR))
      {
        if (LSM303DLHC_Timeout-- == 0) 
        {
          I2C_ClearFlag(LSM303DLHC_I2C,I2C_FLAG_BUSY|I2C_FLAG_AF);
          goto restart4;     
        }         
      }
      __disable_irq();
      /* Clear ADDR */
      temp = LSM303DLHC_I2C->SR2;
      /* Disable ACK */
      I2C_AcknowledgeConfig(LSM303DLHC_I2C, DISABLE);
      __enable_irq();
      while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x0004) != 0x00004); /* Poll on BTF */
       __disable_irq();
      /* Program the STOP */
      I2C_GenerateSTOP(LSM303DLHC_I2C, ENABLE);
      /* Read first data */
      *pBuffer = LSM303DLHC_I2C->DR;
      pBuffer++;
      /* Read second data */
      *pBuffer = LSM303DLHC_I2C->DR;
      __enable_irq();
      LSM303DLHC_I2C->CR1 = 0x0401; /* POS = 0, ACK = 1, PE = 1 */
      
      return SUCCESS;
    }
  else
  {
restart2:
    LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
    /* Send START condition */
    I2C_GenerateSTART(LSM303DLHC_I2C, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {
      if (LSM303DLHC_Timeout-- == 0) return ERROR;
    }
    LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
    /* Send slave address for read */
    I2C_Send7bitAddress(LSM303DLHC_I2C,  DeviceAddr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      
      if (LSM303DLHC_Timeout-- == 0) 
      {
        I2C_ClearFlag(LSM303DLHC_I2C,I2C_FLAG_BUSY|I2C_FLAG_AF);
        goto restart2;
      }
    }
  
    /* While there is data to be read; here the safe procedure is implemented */
    while (NumByteToRead)
    {
  
      if (NumByteToRead != 3) /* Receive bytes from first byte until byte N-3 */
      {
        while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x00004) != 0x000004); /* Poll on BTF */
        /* Read data */
        *pBuffer = I2C_ReceiveData(LSM303DLHC_I2C);
        pBuffer++;
        /* Decrement the read bytes counter */
        NumByteToRead--;
      }
  
      if (NumByteToRead == 3)  /* it remains to read three data: data N-2, data N-1, Data N */
      {
  
        /* Data N-2 in DR and data N -1 in shift register */
        while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x000004) != 0x0000004); /* Poll on BTF */
        /* Clear ACK */
        I2C_AcknowledgeConfig(LSM303DLHC_I2C, DISABLE);
        __disable_irq();
        /* Read Data N-2 */
        *pBuffer = I2C_ReceiveData(LSM303DLHC_I2C);
        pBuffer++;
        /* Program the STOP */
        I2C_GenerateSTOP(LSM303DLHC_I2C, ENABLE);
        /* Read DataN-1 */
        *pBuffer = I2C_ReceiveData(LSM303DLHC_I2C);
        __enable_irq();
        pBuffer++;
        while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x00000040) != 0x0000040); /* Poll on RxNE */
        /* Read DataN */
        *pBuffer = LSM303DLHC_I2C->DR;
        /* Reset the number of bytes to be read by master */
        NumByteToRead = 0;
      }
    }
    /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
    while ((LSM303DLHC_I2C->CR1&0x200) == 0x200);
    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(LSM303DLHC_I2C, ENABLE);
  
    return SUCCESS;
  }
}

/**
  * @brief  Writes one byte to the LSM303DLHC.
  * @param  DeviceAddr : specifies the slave address to be programmed.
  * @param  RegAddr : specifies the LSM303DLHC register to be written.
  * @param NumByteToRead: Number of bytes to be sent to the slave.
  * @param  pBuffer : pointer to the buffer  containing the data to be written to the LSM303DLH.
  * @retval LSM303DLHC Status
 */
uint16_t LSM303DLHC_Write(uint8_t DeviceAddr, uint8_t RegisterAddr,
                               uint16_t NumByteToWrite,
                               uint8_t* pBuffer)
{

  LSM303DLHC_I2C_Config();
  
  restart1:
  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  /* Send START condition */
  I2C_GenerateSTART(LSM303DLHC_I2C, ENABLE);
  /* Test on EV5 and clear it */
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if (LSM303DLHC_Timeout-- == 0) return ERROR;
  }
  /* Send slave address for write */
  I2C_Send7bitAddress(LSM303DLHC_I2C, DeviceAddr, I2C_Direction_Transmitter);

  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  /* Test on EV6 and clear it */
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    
    if (LSM303DLHC_Timeout-- == 0) 
    {
      I2C_ClearFlag(LSM303DLHC_I2C,I2C_FLAG_BUSY|I2C_FLAG_AF);
      goto restart1;
    }
  }

  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;

  /* Transmit the first address for r/w operations */
  I2C_SendData(LSM303DLHC_I2C, RegisterAddr);

  /* Test on EV8 and clear it */
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if (LSM303DLHC_Timeout-- == 0)
      return ERROR;
  }
  if (NumByteToWrite == 0x01)
  {
    LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
    /* Prepare the register value to be sent */
    I2C_SendData(LSM303DLHC_I2C, *pBuffer);

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      if (LSM303DLHC_Timeout-- == 0)
        return ERROR;
    }

    /* End the configuration sequence */
    I2C_GenerateSTOP(LSM303DLHC_I2C, ENABLE);
    return SUCCESS;
  }
  I2C_SendData(LSM303DLHC_I2C, *pBuffer);
  pBuffer++;
  NumByteToWrite--;
  /* While there is data to be written */
  while (NumByteToWrite--)
  {
    while ((I2C_GetLastEvent(LSM303DLHC_I2C) & 0x04) != 0x04);  /* Poll on BTF */
    /* Send the current byte */
    I2C_SendData(LSM303DLHC_I2C, *pBuffer);
    /* Point to the next byte to be written */
    pBuffer++;

  }
  LSM303DLHC_Timeout = LSM303DLHC_LONG_TIMEOUT;
  /* Test on EV8_2 and clear it, BTF = TxE = 1, DR and shift registers are
   empty */
  while (!I2C_CheckEvent(LSM303DLHC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if (LSM303DLHC_Timeout-- == 0) return ERROR;
  }
  /* Send STOP condition */
  I2C_GenerateSTOP(LSM303DLHC_I2C, ENABLE);
  return SUCCESS;
}

/**
  * @brief  Configure the I2C Peripheral used to communicate with LSM303DLHC.
  * @param  None.
  * @retval None.
  */
void LSM303DLHC_I2C_Config(void)
{ 
  I2C_InitTypeDef I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(LSM303DLHC_I2C_SCK_GPIO_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(LSM303DLHC_I2C_SDA_GPIO_CLK, ENABLE);

  /* Connect PB6 and PB7 to LSM303DLHC_I2C*/
  GPIO_PinAFConfig(LSM303DLHC_I2C_SCK_GPIO_PORT, LSM303DLHC_I2C_SCK_SOURCE, LSM303DLHC_I2C_SCK_AF);
  GPIO_PinAFConfig(LSM303DLHC_I2C_SDA_GPIO_PORT, LSM303DLHC_I2C_SDA_SOURCE, LSM303DLHC_I2C_SCK_AF);
  
  /* Configure SCL */
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_I2C_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LSM303DLHC_I2C_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure SDA */
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_I2C_SDA_PIN;
  GPIO_Init(LSM303DLHC_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* LSM303DLHC_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(LSM303DLHC_I2C_CLK, ENABLE);
  
  /* Configure LSM303DLHC_I2C for communication */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x33;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = LSM303DLHC_MAX_COMMUNICATION_FREQ;

  I2C_DeInit(LSM303DLHC_I2C);
  I2C_Cmd(LSM303DLHC_I2C, ENABLE);
  I2C_Init(LSM303DLHC_I2C, &I2C_InitStructure);
  
}
 
/**
* @brief  Initializes the low level interface used to drive the LSM303DLHC
* @param  None
* @retval None
*/
static void LSM303DLHC_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  I2C_InitTypeDef  I2C_InitStructure;
  
  /* Enable the I2C periph */
  RCC_APB1PeriphClockCmd(LSM303DLHC_I2C_CLK, ENABLE);
  
  /* Enable SCK and SDA GPIO clocks */
  RCC_AHB1PeriphClockCmd(LSM303DLHC_I2C_SCK_GPIO_CLK | LSM303DLHC_I2C_SDA_GPIO_CLK , ENABLE);
  
  /* Enable INT1 GPIO clock */
  RCC_AHB1PeriphClockCmd(LSM303DLHC_I2C_INT1_GPIO_CLK, ENABLE);
  
  /* Enable INT2 GPIO clock */
  RCC_AHB1PeriphClockCmd(LSM303DLHC_I2C_INT2_GPIO_CLK, ENABLE);
  
  /* Enable DRDY clock */
  RCC_AHB1PeriphClockCmd(LSM303DLHC_DRDY_GPIO_CLK, ENABLE);
  
  GPIO_PinAFConfig(LSM303DLHC_I2C_SCK_GPIO_PORT, LSM303DLHC_I2C_SCK_SOURCE, LSM303DLHC_I2C_SCK_AF);
  GPIO_PinAFConfig(LSM303DLHC_I2C_SDA_GPIO_PORT, LSM303DLHC_I2C_SDA_SOURCE, LSM303DLHC_I2C_SDA_AF);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* I2C SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_I2C_SCK_PIN;
  GPIO_Init(LSM303DLHC_I2C_SCK_GPIO_PORT, &GPIO_InitStructure);
  
  /* I2C SDA pin configuration */
  GPIO_InitStructure.GPIO_Pin =  LSM303DLHC_I2C_SDA_PIN;
  GPIO_Init(LSM303DLHC_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  /* Mems DRDY */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* Mems DRDY pin configuration */
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_DRDY_PIN;
  GPIO_Init(LSM303DLHC_DRDY_GPIO_PORT, &GPIO_InitStructure);
  
  /* Connect EXTI Line to Mems DRDY Pin */
  SYSCFG_EXTILineConfig(LSM303DLHC_DRDY_EXTI_PORT_SOURCE, LSM303DLHC_DRDY_EXTI_PIN_SOURCE);
  
  EXTI_InitStructure.EXTI_Line = LSM303DLHC_DRDY_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  
  EXTI_Init(&EXTI_InitStructure);
  
  /* I2C configuration -------------------------------------------------------*/
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = LSM303DLHC_MAX_COMMUNICATION_FREQ;
  
  /* Apply LSM303DLHC_I2C configuration after enabling it */
  I2C_Init(LSM303DLHC_I2C, &I2C_InitStructure);
  
  /* LSM303DLHC_I2C Peripheral Enable */
  I2C_Cmd(LSM303DLHC_I2C, ENABLE);
  
  /* Configure GPIO PINs to detect Interrupts */
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_I2C_INT1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(LSM303DLHC_I2C_INT1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LSM303DLHC_I2C_INT2_PIN;
  GPIO_Init(LSM303DLHC_I2C_INT2_GPIO_PORT, &GPIO_InitStructure);
}  

#ifdef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t LSM303DLHC_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  while (1)
  {   
  }
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */ 
  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
