/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dsihost.c
  * @brief   This file provides code for the configuration
  *          of the DSIHOST instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "dsihost.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

DSI_HandleTypeDef hdsi;

/* DSIHOST init function */

void MX_DSIHOST_DSI_Init(void)
{

  /* USER CODE BEGIN DSIHOST_Init 0 */
	HAL_GPIO_WritePin(GPIOG , GPIO_PIN_3 , GPIO_PIN_RESET);
	HAL_Delay(20);/* wait 20 ms */
	HAL_GPIO_WritePin(GPIOG , GPIO_PIN_3, GPIO_PIN_SET);/* Deactivate XRES */
	HAL_Delay(10);/* Wait for 10ms after releasing XRES before sending commands */
  /* USER CODE END DSIHOST_Init 0 */

  DSI_PLLInitTypeDef PLLInit = {0};
  DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
  DSI_PHY_TimerTypeDef PhyTimings = {0};
  DSI_LPCmdTypeDef LPCmd = {0};
  DSI_CmdCfgTypeDef CmdCfg = {0};

  /* USER CODE BEGIN DSIHOST_Init 1 */

  /* USER CODE END DSIHOST_Init 1 */
  hdsi.Instance = DSI;
  hdsi.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
  hdsi.Init.TXEscapeCkdiv = 4;
  hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
  PLLInit.PLLNDIV = 99;
  PLLInit.PLLIDF = DSI_PLL_IN_DIV5;
  PLLInit.PLLODF = DSI_PLL_OUT_DIV1;
  if (HAL_DSI_Init(&hdsi, &PLLInit) != HAL_OK)
  {
    Error_Handler();
  }
  HostTimeouts.TimeoutCkdiv = 1;
  HostTimeouts.HighSpeedTransmissionTimeout = 0;
  HostTimeouts.LowPowerReceptionTimeout = 0;
  HostTimeouts.HighSpeedReadTimeout = 0;
  HostTimeouts.LowPowerReadTimeout = 0;
  HostTimeouts.HighSpeedWriteTimeout = 0;
  HostTimeouts.HighSpeedWritePrespMode = DSI_HS_PM_DISABLE;
  HostTimeouts.LowPowerWriteTimeout = 0;
  HostTimeouts.BTATimeout = 0;
  if (HAL_DSI_ConfigHostTimeouts(&hdsi, &HostTimeouts) != HAL_OK)
  {
    Error_Handler();
  }
  PhyTimings.ClockLaneHS2LPTime = 28;
  PhyTimings.ClockLaneLP2HSTime = 33;
  PhyTimings.DataLaneHS2LPTime = 15;
  PhyTimings.DataLaneLP2HSTime = 25;
  PhyTimings.DataLaneMaxReadTime = 0;
  PhyTimings.StopWaitTime = 0;
  if (HAL_DSI_ConfigPhyTimer(&hdsi, &PhyTimings) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetLowPowerRXFilter(&hdsi, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigErrorMonitor(&hdsi, HAL_DSI_ERROR_NONE) != HAL_OK)
  {
    Error_Handler();
  }
  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_ENABLE;
  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_ENABLE;
  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_ENABLE;
  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_ENABLE;
  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_ENABLE;
  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_ENABLE;
  LPCmd.LPGenLongWrite = DSI_LP_GLW_ENABLE;
  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_ENABLE;
  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_ENABLE;
  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_ENABLE;
  LPCmd.LPDcsLongWrite = DSI_LP_DLW_ENABLE;
  LPCmd.LPMaxReadPacket = DSI_LP_MRDP_ENABLE;
  LPCmd.AcknowledgeRequest = DSI_ACKNOWLEDGE_ENABLE;
  if (HAL_DSI_ConfigCommand(&hdsi, &LPCmd) != HAL_OK)
  {
    Error_Handler();
  }
  CmdCfg.VirtualChannelID = 0;
  CmdCfg.ColorCoding = DSI_RGB888;
  CmdCfg.CommandSize = 400;
  CmdCfg.TearingEffectSource = DSI_TE_EXTERNAL;
  CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
  CmdCfg.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
  CmdCfg.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
  CmdCfg.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
  CmdCfg.VSyncPol = DSI_VSYNC_RISING;
  CmdCfg.AutomaticRefresh = DSI_AR_DISABLE;
  CmdCfg.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_ENABLE;
  if (HAL_DSI_ConfigAdaptedCommandMode(&hdsi, &CmdCfg) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetGenericVCID(&hdsi, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DSIHOST_Init 2 */

  /* USER CODE END DSIHOST_Init 2 */

}

void HAL_DSI_MspInit(DSI_HandleTypeDef* dsiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(dsiHandle->Instance==DSI)
  {
  /* USER CODE BEGIN DSI_MspInit 0 */
	  /** Initializes the peripherals clock
	  */
	    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_DSI;
	    PeriphClkInitStruct.DsiClockSelection = RCC_DSICLKSOURCE_PHY;
	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	    {
	      Error_Handler();
	    }

	    /* DSI clock enable */
	    __HAL_RCC_DSI_CLK_ENABLE();

	    __HAL_RCC_GPIOJ_CLK_ENABLE();
	    /**DSIHOST GPIO Configuration
	    DSI_D1P     ------> DSIHOST_D1P
	    DSI_D1N     ------> DSIHOST_D1N
	    DSI_CKP     ------> DSIHOST_CKP
	    DSI_CKN     ------> DSIHOST_CKN
	    DSI_D0P     ------> DSIHOST_D0P
	    DSI_D0N     ------> DSIHOST_D0N
	    PJ2     ------> DSIHOST_TE
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_2;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF13_DSI;
	    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	    /* DSI interrupt Init */
	    HAL_NVIC_SetPriority(DSI_IRQn, 15, 0);
	    HAL_NVIC_EnableIRQ(DSI_IRQn);
#if 0
  /* USER CODE END DSI_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_DSI;
    PeriphClkInitStruct.DsiClockSelection = RCC_DSICLKSOURCE_PHY;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* DSI clock enable */
    __HAL_RCC_DSI_CLK_ENABLE();

    __HAL_RCC_GPIOJ_CLK_ENABLE();
    /**DSIHOST GPIO Configuration
    DSI_D1P     ------> DSIHOST_D1P
    DSI_D1N     ------> DSIHOST_D1N
    DSI_CKP     ------> DSIHOST_CKP
    DSI_CKN     ------> DSIHOST_CKN
    DSI_D0P     ------> DSIHOST_D0P
    DSI_D0N     ------> DSIHOST_D0N
    PJ2     ------> DSIHOST_TE
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_DSI;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    /* DSI interrupt Init */
    HAL_NVIC_SetPriority(DSI_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(DSI_IRQn);
  /* USER CODE BEGIN DSI_MspInit 1 */
#endif
  /* USER CODE END DSI_MspInit 1 */
  }
}

void HAL_DSI_MspDeInit(DSI_HandleTypeDef* dsiHandle)
{

  if(dsiHandle->Instance==DSI)
  {
  /* USER CODE BEGIN DSI_MspDeInit 0 */

  /* USER CODE END DSI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DSI_CLK_DISABLE();

    /**DSIHOST GPIO Configuration
    DSI_D1P     ------> DSIHOST_D1P
    DSI_D1N     ------> DSIHOST_D1N
    DSI_CKP     ------> DSIHOST_CKP
    DSI_CKN     ------> DSIHOST_CKN
    DSI_D0P     ------> DSIHOST_D0P
    DSI_D0N     ------> DSIHOST_D0N
    PJ2     ------> DSIHOST_TE
    */
    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_2);

    /* DSI interrupt Deinit */
    HAL_NVIC_DisableIRQ(DSI_IRQn);
  /* USER CODE BEGIN DSI_MspDeInit 1 */

  /* USER CODE END DSI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
