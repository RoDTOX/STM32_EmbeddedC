/*
 * pn532.h
 *
 *  Created on: May 30, 2024
 *      Author: bogdsece
 */

#ifndef PN532_H
#define PN532_H

#define ENABLE_USART 1
#define ENABLE_I2C 0

//-------------
#if ENABLE_USART
#include "main.h"
//#include "usart.h"

HAL_StatusTypeDef PN532_SendCommand(uint8_t* cmd, uint8_t cmd_len);
HAL_StatusTypeDef PN532_ReadResponse(uint8_t* buffer, uint8_t buffer_len);
extern void PN532_GetFirmwareVersion(void);
extern void PN532_Wakeup(void);

#endif // ENABLE_USART
//-------------

//-------------
#if ENABLE_I2C
#include "main.h"
//#include "i2c.h"

#define PN532_I2C_ADDRESS 0x24 // Default I2C address for PN532 is 0x48 shifted right 1 bit

HAL_StatusTypeDef PN532_SendCommand(uint8_t* cmd, uint8_t cmd_len);
HAL_StatusTypeDef PN532_ReadResponse(uint8_t* buffer, uint8_t buffer_len);
void PN532_GetFirmwareVersion(void);

#endif // ENABLE_I2C
//-------------

#endif // PN532_H
