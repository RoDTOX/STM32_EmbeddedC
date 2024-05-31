/*
 * pn532.c
 *
 *  Created on: May 30, 2024
 *      Author: bogdsece
 */

#include <pn532_sbc.h>
#include <stdio.h>

//-------------
#if ENABLE_I2C

extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef PN532_SendCommand(uint8_t* cmd, uint8_t cmd_len)
{
    return HAL_I2C_Master_Transmit(&hi2c1, PN532_I2C_ADDRESS << 1, cmd, cmd_len, HAL_MAX_DELAY);
}

HAL_StatusTypeDef PN532_ReadResponse(uint8_t* buffer, uint8_t buffer_len)
{
    return HAL_I2C_Master_Receive(&hi2c1, PN532_I2C_ADDRESS << 1, buffer, buffer_len, HAL_MAX_DELAY);
}

#endif //ENABLE_I2C
//-------------

//-------------
#if ENABLE_USART

extern UART_HandleTypeDef huart2; // Adjust this if you're using a different UART

HAL_StatusTypeDef PN532_SendCommand(uint8_t* cmd, uint8_t cmd_len)
{
	return HAL_UART_Transmit(&huart2, cmd, cmd_len, HAL_MAX_DELAY);
}

HAL_StatusTypeDef PN532_ReadResponse(uint8_t* buffer, uint8_t buffer_len)
{
	return HAL_UART_Receive(&huart2, buffer, buffer_len, HAL_MAX_DELAY);
}

#endif //ENABL_USART
//-------------

//-------------
void PN532_Wakeup()
{
	// Wake up the PN532
	uint8_t wakeup_cmd[] = {0x55};

	if (HAL_UART_Transmit(&huart2, wakeup_cmd, 1, HAL_MAX_DELAY) != HAL_OK)
	{
	  printf("Failed to wake up PN532\n");
	  Error_Handler();
	}
	else
	{
	  printf("PN532 wakeup command sent\n");
	  if (HAL_UART_Transmit(&huart2, wakeup_cmd, 1, HAL_MAX_DELAY) != HAL_OK)
	  	{
	  	  printf("Failed to wake up PN532\n");
	  	  Error_Handler();
	  	}
	}
	HAL_UART_Transmit(&huart2, 0, 1, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, 0, 1, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, 0, 1, HAL_MAX_DELAY);

	HAL_Delay(1000); // Delay to allow PN532 to wake up
}
//-------------


//-------------
void PN532_GetFirmwareVersion(void)
{
	uint8_t response[20];
	HAL_StatusTypeDef PN532_ReqStatus = 0;
    uint8_t get_firmware_cmd[] = {
        0x00, 0x00, 0xFF, // Preamble and start code
        0x02, 0xFE, // Length and LCS
        0xD4, 0x02, // TFI and command code
        0x2A, // DCS
        0x00 // Postamble
    };

    PN532_ReqStatus = PN532_SendCommand(get_firmware_cmd, sizeof(get_firmware_cmd));
    if (PN532_ReqStatus == HAL_OK)
    {
    	printf("PN532_GetFirmwareVersion command sent!\n");
    }
    else
    {
    	printf("Error in send PN532_GetFirmwareVersion!\n");
        Error_Handler();
    }

    PN532_ReqStatus = PN532_ReadResponse(response, sizeof(response));
    if (PN532_ReqStatus == HAL_OK)
    {
    	printf("Response of PN532_GetFirmwareVersion = %s\n",&response[0]);
    }
    else
    {
    	printf("Error in reading PN532_GetFirmwareVersion!\n");
        Error_Handler();
    }

    // Process the response to get firmware version
    printf("Firmware version response: ");
    for (int i = 0; i < sizeof(response); i++)
    {
        printf("%02X ", response[i]);
    }
    printf("\n");

    // Process the response to get firmware version
    // Print the response or check specific bytes in the response
    // You can use a debugger or printf to check the response
}
//-------------
/*
// Define positions and masks for control bits in USART_CR1 register
#define USART_CR1_SBK_Pos             (0U)
#define USART_CR1_SBK_Msk             (0x1UL << USART_CR1_SBK_Pos)
#define USART_CR1_SBK                 USART_CR1_SBK_Msk    // Send Break

#define USART_CR1_RWU_Pos             (1U)
#define USART_CR1_RWU_Msk             (0x1UL << USART_CR1_RWU_Pos)
#define USART_CR1_RWU                 USART_CR1_RWU_Msk    // Receiver wakeup

#define USART_CR1_RE_Pos              (2U)
#define USART_CR1_RE_Msk              (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_RE                  USART_CR1_RE_Msk     // Receiver Enable

#define USART_CR1_TE_Pos              (3U)
#define USART_CR1_TE_Msk              (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE                  USART_CR1_TE_Msk     // Transmitter Enable

#define USART_CR1_IDLEIE_Pos          (4U)
#define USART_CR1_IDLEIE_Msk          (0x1UL << USART_CR1_IDLEIE_Pos)
#define USART_CR1_IDLEIE              USART_CR1_IDLEIE_Msk // IDLE Interrupt Enable

#define USART_CR1_RXNEIE_Pos          (5U)
#define USART_CR1_RXNEIE_Msk          (0x1UL << USART_CR1_RXNEIE_Pos)
#define USART_CR1_RXNEIE              USART_CR1_RXNEIE_Msk // RXNE Interrupt Enable

#define USART_CR1_TCIE_Pos            (6U)
#define USART_CR1_TCIE_Msk            (0x1UL << USART_CR1_TCIE_Pos)
#define USART_CR1_TCIE                USART_CR1_TCIE_Msk   // Transmission Complete Interrupt Enable

#define USART_CR1_TXEIE_Pos           (7U)
#define USART_CR1_TXEIE_Msk           (0x1UL << USART_CR1_TXEIE_Pos)
#define USART_CR1_TXEIE               USART_CR1_TXEIE_Msk  // TXE Interrupt Enable

#define USART_CR1_PEIE_Pos            (8U)
#define USART_CR1_PEIE_Msk            (0x1UL << USART_CR1_PEIE_Pos)
#define USART_CR1_PEIE                USART_CR1_PEIE_Msk   // PE Interrupt Enable

#define USART_CR1_PS_Pos              (9U)
#define USART_CR1_PS_Msk              (0x1UL << USART_CR1_PS_Pos)
#define USART_CR1_PS                  USART_CR1_PS_Msk     // Parity Selection

#define USART_CR1_PCE_Pos             (10U)
#define USART_CR1_PCE_Msk             (0x1UL << USART_CR1_PCE_Pos)
#define USART_CR1_PCE                 USART_CR1_PCE_Msk    // Parity Control Enable

#define USART_CR1_WAKE_Pos            (11U)
#define USART_CR1_WAKE_Msk            (0x1UL << USART_CR1_WAKE_Pos)
#define USART_CR1_WAKE                USART_CR1_WAKE_Msk   // Wakeup method

#define USART_CR1_M_Pos               (12U)
#define USART_CR1_M_Msk               (0x1UL << USART_CR1_M_Pos)
#define USART_CR1_M                   USART_CR1_M_Msk      // Word length

#define USART_CR1_UE_Pos              (13U)
#define USART_CR1_UE_Msk              (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_UE                  USART_CR1_UE_Msk     // USART Enable

#define USART_CR1_OVER8_Pos           (15U)
#define USART_CR1_OVER8_Msk           (0x1UL << USART_CR1_OVER8_Pos)
#define USART_CR1_OVER8               USART_CR1_OVER8_Msk  // USART Oversampling by 8 enable
*/
