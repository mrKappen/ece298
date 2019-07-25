#include <msp430fr4133.h>

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#define pos1 4   /* Digit A1 - L4  */
#define pos2 6   /* Digit A2 - L6  */
#define pos3 8   /* Digit A3 - L8  */
#define pos4 10  /* Digit A4 - L10 */
#define pos5 2   /* Digit A5 - L2  */
#define pos6 18  /* Digit A6 - L18 */

// Define word access definitions to LCD memories
#define LCDMEMW ((int*)LCDMEM)

// Workaround LCDBMEM definition bug in IAR header file
#ifdef __IAR_SYSTEMS_ICC__
#define LCDBMEMW ((int*)&LCDM32)
#else
#define LCDBMEMW ((int*)LCDBMEM)
#endif

extern const char digit[10][2];
extern const char alphabetBig[26][2];

void Init_LCD(void);
void displayScrollText(char*);
void showChar(char, int);
void showHex(int hex);
void clearLCD(void);


#endif /* HAL_LCD_H_ */
