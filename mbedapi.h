#ifndef _MBEDAPI_H_
#define _MBEDAPI_H_

#ifdef __cplusplus
  #define MBEDAPI extern "C"
#else
  #define MBEDAPI
#endif

// typedef enum {
//   MBED_D0, MBED_D1, MBED_D2, MBED_D3, MBED_D4, MBED_D5, MBED_D6, MBED_D7,
//   MBED_D8, MBED_D9, MBED_D10, MBED_D11, MBED_D12, MBED_D13, MBED_D14, MBED_D15,
//   MBED_A0, MBED_A1, MBED_A2, MBED_A3, MBED_A4, MBED_A5,
//   MBED_LED1, MBED_LED2, MBED_LED3, MBED_LED4,
//   MBED_BUTTON1
// } MBED_PINS;

// #define MBED_LED1     0
// #define MBED_LED2     1
// #define MBED_LED3     2
// #define MBED_LED4     3
// #define MBED_BUTTON1  4

/* Time */
MBEDAPI void MBED_wait_ms(int);
MBEDAPI void MBED_wait_us(int);
MBEDAPI void MBED_start_ticker(void);
MBEDAPI long MBED_millis(void);

/* UART / VCP */
MBEDAPI int MBED_printf(const char*, ...);
MBEDAPI void MBED_putc(char);
MBEDAPI int MBED_getc(void);

/* Digital IO */
MBEDAPI void digitalWrite(int, int);
MBEDAPI int digitalRead(int);

/* I2C */
MBEDAPI int i2cWrite(int, const char*, int, uint8_t);
MBEDAPI int i2cRead(int, char*, int);
MBEDAPI void i2cStart(void);
MBEDAPI void i2cEnd(void);
MBEDAPI int i2cReadRaw(int);
MBEDAPI int i2cWriteRaw(int);

#endif /* _MBEDAPI_H_ */
