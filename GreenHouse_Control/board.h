enum sensorChoice { M1, M2, M3, T1, T2, T3 };

void initPorts();
void setUpAdcs();
void toggleLed(int);
void toggleBuzzer();

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __MSP430FR4133__

/* output port for buzzer */
#define BUZZER_PORT     GPIO_PORT_P1
#define BUZZER_PIN      GPIO_PIN7

/* first moisture sensor */
#define M1_PORT         GPIO_PORT_P8
#define M1_PIN          GPIO_PIN1

/* second moisture sensor */
#define M2_PORT         GPIO_PORT_P8
#define M2_PIN          GPIO_PIN0

/* third moisture sensor */
#define M3_PORT         GPIO_PORT_P1
#define M3_PIN          GPIO_PIN1

/* first temperature sensor */
#define T1_PORT         GPIO_PORT_P1
#define T1_PIN          GPIO_PIN5

/* second temperature sensor */
#define T2_PORT         GPIO_PORT_P1
#define T2_PIN          GPIO_PIN4

/* third temperature sensor */
#define T3_PORT         GPIO_PORT_P1
#define T3_PIN          GPIO_PIN3

/* first LED (on address P1.0) */
#define LED1_PORT       GPIO_PORT_P1
#define LED1_PIN        GPIO_PIN0

/* second LED (on address P4.0) */
#define LED2_PORT       GPIO_PORT_P4
#define LED2_PIN        GPIO_PIN0

/* launchPad Pushbutton Switch 1 */
#define SW1_PORT        GPIO_PORT_P1
#define SW1_PIN         GPIO_PIN2

/* launchPad Pushbutton Switch 2 */
#define SW2_PORT        GPIO_PORT_P2
#define SW2_PIN         GPIO_PIN6

#endif // __MSP430FR4133__

#endif // __BOARD_H__

