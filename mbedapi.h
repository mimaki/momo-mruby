#ifndef _MBEDAPI_H_
#define _MBEDAPI_H_

#ifdef __cplusplus
  #define MBEDAPI extern "C"
#else
  #define MBEDAPI
#endif

#define MBED_LED1     0
#define MBED_LED2     1
#define MBED_LED3     2
#define MBED_LED4     3
#define MBED_BUTTON1  4

MBEDAPI int MBED_printf(const char*, ...);
MBEDAPI void MBED_putc(char);
MBEDAPI int MBED_getc(void);

MBEDAPI void digitalWrite(int, int);
MBEDAPI int digitalRead(int);

#endif /* _MBEDAPI_H_ */
