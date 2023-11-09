#ifndef __IS3xFL323_H
#define __IS3xFL323_H

#define SHUTDOWN_REG          0x00
#define PWM_OUTPUT_REG_START  0x01
#define PWM_OUTPUT_REG_END    0x24
#define PWM_UPDATE_REG        0x25
#define LED_CONTROL_REG_START 0x26
#define LED_CONTROL_REG_END   0x49
#define GLOBAL_CONTORL_REG    0x4A
#define OUTPUT_FREQ_REG       0x4B
#define RESET_REG             0x4F

/*
    A7:A3 = 01111,A0 = 0
    if  AD connected to GND,AD = 00;
        AD connected to VCC,AD = 11;
        AD connected to SCL,AD = 01;
        AD connected to SDA,AD = 10;
        if AD = 0,addr = 0x01111000 = 0x78
*/
#define LED_ADDRESS  0x78
void IS3xFL323x_Init(void);
void IS3xFL323x_Flow(void);
void IS3xFL323x_ALL_ON(void);
#endif
