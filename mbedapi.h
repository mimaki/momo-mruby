#ifndef _MBEDAPI_H_
#define _MBEDAPI_H_

#ifdef __cplusplus
  #define MBEDAPI extern "C"
#else
  #define MBEDAPI
#endif

#define MBED_SERIAL_PARITY_NONE 0
#define MBED_SERIAL_PARITY_ODD  1
#define MBED_SERIAL_PARITY_EVEN 2

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

#endif /* _MBEDAPI_H_ */
