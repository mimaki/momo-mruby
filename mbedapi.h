#ifndef _MBEDAPI_H_
#define _MBEDAPI_H_

#ifdef __cplusplus
  #define MBEDAPI extern "C"
#else
  #define MBEDAPI
#endif

/* GPIO pins */
typedef enum {
  MBED_D0, MBED_D1, MBED_D2, MBED_D3, MBED_D4, MBED_D5, MBED_D6, MBED_D7,
  MBED_D8, MBED_D9, MBED_D10, MBED_D11, MBED_D12, MBED_D13, MBED_D14, MBED_D15,
  MBED_A0, MBED_A1, MBED_A2, MBED_A3, MBED_A4, MBED_A5,
  MBED_LED1, MBED_LED2, MBED_LED3, MBED_LED4,
  MBED_BUTTON1
} mbedGPIOpins;

/* Serial(UART) parity */
#define MBED_SERIAL_PARITY_NONE 0
#define MBED_SERIAL_PARITY_ODD  1
#define MBED_SERIAL_PARITY_EVEN 2

/* mbed API functions */

/* Time */
MBEDAPI void mbedDelay(int);
MBEDAPI void mbedDelay_us(int);
MBEDAPI long mbedMillis(void);
MBEDAPI void mbedStartTicker(void);

/* VCP */
MBEDAPI int mbedPrintf(const char*, ...);
MBEDAPI void mbedPutc(char);
MBEDAPI int mbedGetc(void);

/* Serial(UART) */
MBEDAPI void *mbedSerialInit(int, int, int, int, int);
MBEDAPI int mbedSerialRawRead(void*);
MBEDAPI int mbedSerialRawWrite(void*, int);
MBEDAPI int mbedSerialAvailable(void*);
MBEDAPI int mbedSerialFlush(void*);
MBEDAPI int mbedSerialClose(void*);

/* Digital IO */
MBEDAPI void mbedDigitalWrite(int, int);
MBEDAPI int mbedDigitalRead(int);

/* I2C */
MBEDAPI int mbedI2CWrite(int, const char*, int, uint8_t);
MBEDAPI int mbedI2CRead(int, char*, int);
MBEDAPI void mbedI2CStart(void);
MBEDAPI void mbedI2CStop(void);

/* SPI */
MBEDAPI void *mbedSPIInit(int, int);
MBEDAPI int mbedSPITransfer(void*, int);
MBEDAPI void mbedSPIClose(void*);

#endif /* _MBEDAPI_H_ */
