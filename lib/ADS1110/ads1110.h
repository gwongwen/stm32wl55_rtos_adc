/* @file    ads1110.h -------------------------------------------------------------------------*/
/* @brief   ADS1110 ADC driver ----------------------------------------------------------------*/

/* define to prevent recursive inclusion ------------------------------------------------------*/
#ifndef	_ADS1110_H_
#define _ADS1110_H_

#ifdef __cplusplus
extern "C" {
#endif

/* includes -----------------------------------------------------------------------------------*/
#include <stdint.h>

/* I2C device address -------------------------------------------------------------------------*/
#define ADS1110_I2C_ADDRESS_BASE    0x48

typedef enum ADS1110_Address_e
{
  ADS1110_ADDRESS_A0 = ADS1110_I2C_ADDRESS_BASE,
  ADS1110_ADDRESS_A1,
  ADS1110_ADDRESS_A2,
  ADS1110_ADDRESS_A3,
  ADS1110_ADDRESS_A4,
  ADS1110_ADDRESS_A5,
  ADS1110_ADDRESS_A6,
  ADS1110_ADDRESS_A7,
} ADS1110_Address_t;

/* libraries functions ------------------------------------------------------------------------*/
typedef enum ADS1110_Result_e
{
  ADS1110_OK              = 0,
  ADS1110_FAIL            = 1,
  ADS1110_INVALID_PARAM   = 2,
  ADS1110_DATA_NOT_READY  = 3
} ADS1110_Result_t;

/* measuring mode ----------------------------------------------------------------------------*/
typedef enum ADS1110_Mode_e
{
  ADS1110_MODE_CONTINUOUS = 0,
  ADS1110_MODE_SINGLESHOT = 1
} ADS1110_Mode_t;

/* measuring speed in period mode ------------------------------------------------------------*/
typedef enum ADS1110_Rate_e
{
  ADS1110_RATE_240MPS  = 0,
  ADS1110_RATE_60MPS   = 1,
  ADS1110_RATE_30MPS   = 2,
  ADS1110_RATE_15MPS   = 3
} ADS1110_Rate_t;

/* PGA gain ----------------------------------------------------------------------------------*/
typedef enum ADS1110_Gain_e
{
  ADS1110_GAIN_1  = 0,
  ADS1110_GAIN_2  = 1,
  ADS1110_GAIN_4  = 2,
  ADS1110_GAIN_8  = 3,
} ADS1110_Gain_t;

/* sample -------------------------------------------------------------------------------------*/
typedef struct ADS1110_Sample_s
{
  int16_t Raw;
  float Voltage;
} ADS1110_Sample_t;

/* function type initialize/deinitialize platform dependent layer ------------------------------*/
typedef int8_t (*ADS1110_PlatformInitDeinit_t)(void);

/* function type for send/receive data to/from the slave ---------------------------------------*/
typedef int8_t (*ADS1110_PlatformSendReceive_t)(uint8_t Address, uint8_t *Data, uint8_t Len);

/* handler data type ---------------------------------------------------------------------------*/
typedef struct ADS1110_Handler_s
{
  ADS1110_Address_t AddressI2C;
  ADS1110_Mode_t Mode;
  ADS1110_Gain_t Gain;
  ADS1110_Rate_t Rate;

  // Initializes platform dependent layer
  ADS1110_PlatformInitDeinit_t PlatformInit;
  // De-initializes platform dependent layer
  ADS1110_PlatformInitDeinit_t PlatformDeInit;
  // Send Data to the ADS1110
  ADS1110_PlatformSendReceive_t PlatformSend;
  // Receive Data from the ADS1110
  ADS1110_PlatformSendReceive_t PlatformReceive;
} ADS1110_Handler_t;

/* initializer function ------------------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_Init(ADS1110_Handler_t *Handler, ADS1110_Address_t Address);

/* deinitializer function ----------------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_DeInit(ADS1110_Handler_t *Handler);

/* send general call reset command function ----------------------------------------------------*/
ADS1110_Result_t
ADS1110_GeneralCallReset(ADS1110_Handler_t *Handler);

/* set measurement mode function ---------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_SetMode(ADS1110_Handler_t *Handler, ADS1110_Mode_t Mode);

/* set PGA gain function -----------------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_SetGain(ADS1110_Handler_t *Handler, ADS1110_Gain_t Gain);

/* set measurement rate function ---------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_SetRate(ADS1110_Handler_t *Handler, ADS1110_Rate_t Rate);

/* start conversion  function ------------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_StartConversion(ADS1110_Handler_t *Handler);

/* check if data is deady function -------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_CheckDataReady(ADS1110_Handler_t *Handler);

/* read sample function ------------------------------------------------------------------------*/
ADS1110_Result_t
ADS1110_ReadSample(ADS1110_Handler_t *Handler, ADS1110_Sample_t *Sample);

#ifdef __cplusplus
}
#endif

#endif //! _ADS1110_H_