#include <msp430.h> 
#include <board.h>
#include "LCD_Files/hal_LCD.h"
#include "MSP430FR2xx_4xx/driverlib.h"

enum sensorChoice currentSensor = T1;
int count = 0;

void main() {
    // disable interrupts for all initializations
    __disable_interrupt();
    WDT_A_hold(WDT_A_BASE);
    Init_LCD();
    initPorts();
    PMM_unlockLPM5();
    __enable_interrupt();

    while(1) {
        displayScrollText("GREENHOUSE CONTROL");
        _delay_cycles(100000);
        break;
    }

    while(GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 1 && GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 1) {
        displayScrollText("PRESS ANY BUTTON TO BEGIN");
    }

    setUpAdcs();
    return;
}

void toggleLed(int choice) {
    int count = 0;
    switch(choice) {
    case 1: // TURN ON LED 1.0
        WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
        PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
        P1DIR |= 0x01;                          // Set P1.0 to output direction (RED)

        count = 0;
        while(1) {
            volatile unsigned int i;            // volatile to prevent optimization
            P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR
            count++;
            if(count == 25) break;
            i = 10000;                          // SW Delay
            do i--;
            while(i != 0);
        }
        break;

    case 2: // TURN ON LED 4.0
        WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
        PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
        P4DIR |= 0x01;                          // Set P4.0 to output direction (GREEN)

        count = 0;
        while(1) {
            volatile unsigned int i;            // volatile to prevent optimization
            P4OUT ^= 0x01;                      // Toggle P4.0 using exclusive-OR
            count++;
            if(count == 25) break;
            i = 10000;                          // SW Delay
            do i--;
            while(i != 0);
        }
        break;

    default: break;
    }
}

void toggleBuzzer() {
    initPorts();
    int buzzerCount = 0;
    while(1) {
        GPIO_setOutputHighOnPin(BUZZER_PORT, BUZZER_PIN);
        _delay_cycles(500);
        GPIO_setOutputLowOnPin(BUZZER_PORT, BUZZER_PIN);
        _delay_cycles(500);
        buzzerCount++;
        if (buzzerCount == 2000) break;
    }
}

void initPorts() {
    // initialize all ports for the 6 sensors
    GPIO_setAsPeripheralModuleFunctionInputPin(M1_PORT, M1_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize first moisture sensor
    GPIO_setAsPeripheralModuleFunctionInputPin(M2_PORT, M2_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize second moisture sensor
    GPIO_setAsPeripheralModuleFunctionInputPin(M3_PORT, M3_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize third moisture sensor
    GPIO_setAsPeripheralModuleFunctionInputPin(T1_PORT, T1_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize first temperature sensor
    GPIO_setAsPeripheralModuleFunctionInputPin(T2_PORT, T2_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize second temperature sensor
    GPIO_setAsPeripheralModuleFunctionInputPin(T3_PORT, T3_PIN, GPIO_PRIMARY_MODULE_FUNCTION);    // initialize third temperature sensor

    // initialize the port for the buzzer
    //GPIO_setAsPeripheralModuleFunctionOutputPin(BUZZER_PORT, BUZZER_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(BUZZER_PORT, BUZZER_PIN);

    // set all GPIO pins to output low to prevent floating input and reduce power consumption
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    // set LaunchPad switches as inputs - they are active low, meaning '1' until pressed
    GPIO_setAsInputPinWithPullUpResistor(SW1_PORT, SW1_PIN);
    GPIO_setAsInputPinWithPullUpResistor(SW2_PORT, SW2_PIN);
}

void setUpAdcs() {
    PMM_unlockLPM5();

    // initialize the ADC Module
    ADC_init(ADC_BASE, ADC_SAMPLEHOLDSOURCE_SC, ADC_CLOCKSOURCE_ADCOSC, ADC_CLOCKDIVIDER_1);
    ADC_enable(ADC_BASE);


    while(1) {
        ADC_setupSamplingTimer(ADC_BASE, ADC_CYCLEHOLD_16_CYCLES, ADC_MULTIPLESAMPLESDISABLE);        // timer trigger needed to start every ADC conversion
        ADC_configureMemory(ADC_BASE, ADC_INPUT_A9, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
        ADC_clearInterrupt(ADC_BASE, ADC_COMPLETED_INTERRUPT);                                        // receiving new (voltage) data, disable the interrupt request to stick with current value
        ADC_enableInterrupt(ADC_BASE, ADC_COMPLETED_INTERRUPT);

        //Configure internal reference- return the ready status of the variable reference voltage
        //If ref voltage no ready, WAIT
        while (PMM_REFGEN_NOTREADY == PMM_getVariableReferenceVoltageStatus()) ;

        //Internal Reference ON
        PMM_enableInternalReference();      // disabled by default
        __bis_SR_register(GIE);           // LPM0, TA0_ISR will force exit

        count = 0;

        while(1) {
            // configure ADC memory for first moisture sensor
            while (currentSensor == M1) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A9, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);
                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = M2;
                    count = 0;
                }
            }

            // configure ADC memory for second moisture sensor
            while (currentSensor == M2) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A8, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);

                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = M3;
                    count = 0;
                }
            }

            // configure ADC memory for third moisture sensor
            while (currentSensor == M3) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A1, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);
                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = T1;
                    count = 0;
                }
            }

            // configure ADC memory for first temperature sensor
            while (currentSensor == T1) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A5, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);
                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = T2;
                    count = 0;
                }
            }

            // configure ADC memory for second temperature sensor
            while (currentSensor == T2) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A4, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);

                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = T3;
                    count = 0;
                }
            }

            // configure ADC memory for third temperature sensor
            while (currentSensor == T3) {
                ADC_configureMemory(ADC_BASE, ADC_INPUT_A3, ADC_VREFPOS_INT, ADC_VREFNEG_AVSS);
                ADC_startConversion(ADC_BASE, ADC_SINGLECHANNEL);
                _delay_cycles(5000);
                count++;
                if (count == 2000) {
                    currentSensor = M1;
                    count = 0;
                }
            }
        }
    }
}

//ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC_VECTOR)))
#endif
void ADC_ISR (void) {
    switch (__even_in_range(ADCIV,12)){     // interrupt vector register never has a value that is odd or larger than 12 (stated)
        case  0: break; //No interrupt
        case  2: break; //conversion result overflow
        case  4: break; //conversion time overflow
        case  6: break; //ADCHI
        case  8: break; //ADCLO
        case 10: break; //ADCIN
        case 12:        //ADCIFG0 is ADC interrupt flag

            if (currentSensor == M1) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x100) { // LESS THAN 1 V
                        toggleLed(1);
                        toggleBuzzer();
                        proceedToBreak = 0;
                        displayScrollText("ZONE 1 MOISTURE LOW");
                    } else {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 MOISTURE GOOD");
                    }
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = M2;
                        break;
                    }
                }
            } else if (currentSensor == M2) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x100) { // LESS THAN 1 V
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 2 MOISTURE LOW");
                    } else {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 MOISTURE GOOD");
                    }
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = M3;
                        break;
                    }
                }
            } else if (currentSensor == M3) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x100) { // LESS THAN 1 V
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 3 MOISTURE LOW");
                    } else {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 MOISTURE GOOD");
                    }
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = T1;
                        break;
                    }
                }
            } else if (currentSensor == T1) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x155) { // if voltage less than 0.5 V, then temperature is less than 0
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 1 BELOW 0 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x199) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 1 AROUND 10 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1DD) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AROUND 20 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1E4) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 21 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1EB) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 22 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F2) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 23 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F9) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 24 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x200) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 25 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x207) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 26 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x20E) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 27 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x215) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 28 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x21C) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AT 29 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x222) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 1 AROUND 30 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x266) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 1 AROUND 37 C");
                    } else {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 1 ABOVE 37 C");
                    }
                    _delay_cycles(100000);
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = T2;
                        break;
                    }
                }
            } else if (currentSensor == T2) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x155) { // if voltage less than 0.5 V, then temperature is less than 0
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 2 BELOW 0 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x199) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 2 AROUND 10 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1DD) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AROUND 20 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1E4) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 21 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1EB) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 22 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F2) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 23 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F9) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 24 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x200) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 25 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x207) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 26 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x20E) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 27 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x215) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 28 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x21C) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AT 29 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x222) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 2 AROUND 30 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x266) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 2 AROUND 37 C");
                    } else {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 2 ABOVE 37 C");
                    }
                    _delay_cycles(100000);
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = T3;
                        break;
                    }
                }
            } else if (currentSensor == T3) {
                int proceedToBreak;
                P1DIR = P4DIR = 0x0;
                _delay_cycles(5000);
                while(1) {
                    if (ADC_getResults(ADC_BASE) < 0x155) { // if voltage less than 0.5 V, then temperature is less than 0
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 3 BELOW 0 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x199) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 3 AROUND 10 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1DD) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AROUND 20 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1E4) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 21 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1EB) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 22 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F2) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 23 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x1F9) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 24 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x200) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 25 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x207) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 26 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x20E) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 27 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x215) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 28 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x21C) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AT 29 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x222) {
                        toggleLed(2);
                        proceedToBreak = 1;
                        displayScrollText("ZONE 3 AROUND 30 C");
                    } else if (ADC_getResults(ADC_BASE) < 0x266) {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 3 AROUND 37 C");
                    } else {
                        toggleBuzzer();
                        toggleLed(1);
                        proceedToBreak = 0;
                        displayScrollText("ZONE 3 ABOVE 37 C");
                    }
                    _delay_cycles(100000);
                    if(proceedToBreak || GPIO_getInputPinValue(SW1_PORT, SW1_PIN) == 0 || GPIO_getInputPinValue(SW2_PORT, SW2_PIN) == 0) {
                        count = 0;
                        currentSensor = M1;
                        break;
                    }
                }
            }
        break;

        default: break;
    }
}
