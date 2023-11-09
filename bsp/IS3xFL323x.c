
#include "IS3xFL323x.h"


//hal lib
#include "stm32f1xx_hal.h"
#include "i2c.h"


unsigned char leds[][3] = {
  //RGB LED format:
  //{R,  G,  B} 
  {20,  10,  30},  // D40
  {50,  40,  60},  // D41
  {80,  70,  90},  // D42
  {50, 60, 70}, // D43
  {14, 13, 15}, // D44
  {17, 16, 18}, // D45
  {20, 19, 21}, // D46
  {23, 22, 24}, // D47
  {26, 25, 27}, // D48
  {29, 28, 30}, // D49
  {32, 31, 33}, // D50
  {35, 34, 36}  // D51
};


void fx_i2c(uint8_t addr,uint8_t offset,uint8_t value)
{
	uint8_t w_buffer[2];
   // uint32_t ret;

	w_buffer[0] = offset;
	w_buffer[1] = value;
    HAL_I2C_Master_Transmit(&hi2c1,LED_ADDRESS,w_buffer,2,20);
}


void IS3xFL323x_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    uint8_t offset = 0;

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_RESET);

    /*Configure GPIO pins : PB8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, GPIO_PIN_SET);//第一次拉高

    for(offset = LED_CONTROL_REG_START;offset <= LED_CONTROL_REG_END;offset++ )
    {
    fx_i2c(LED_ADDRESS,offset,0xFF);
    }

    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
    fx_i2c(LED_ADDRESS,offset,0xFF);
    }

    fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);
    fx_i2c(LED_ADDRESS,OUTPUT_FREQ_REG,0x01);
    fx_i2c(LED_ADDRESS,SHUTDOWN_REG,0x01);

}

void IS3xFL323x_Flow(void)
{
    uint8_t offset = 0;
    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
    if(offset % 3 == 0)
    {
        fx_i2c(LED_ADDRESS,offset,leds[offset/3][0]);
        fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);
        HAL_Delay(150);
    }
    if(offset % 3 == 1)
    {
        fx_i2c(LED_ADDRESS,offset,leds[offset/3][1]);
    }
    if(offset % 3 ==2)
    {
        fx_i2c(LED_ADDRESS,offset,leds[offset/3][2]);
    }
    }
    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
        fx_i2c(LED_ADDRESS,offset,0x00);
    }
        fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);

    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
        if(offset % 3 == 0)
    {
        fx_i2c(LED_ADDRESS,PWM_OUTPUT_REG_END-offset+1,offset*7);
        fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);
        HAL_Delay(150);
    }
    if(offset % 3 == 1)
    {
        fx_i2c(LED_ADDRESS,PWM_OUTPUT_REG_END-offset+1,255-offset*7);
    }
    if(offset % 3 ==2)
    {
        fx_i2c(LED_ADDRESS,PWM_OUTPUT_REG_END-offset+1,128-offset*2);
    }
    }
    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
        fx_i2c(LED_ADDRESS,offset,0x00);
    }
    fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);
}


void IS3xFL323x_ALL_ON(void)
{
    uint8_t offset = 0;
    for(offset = PWM_OUTPUT_REG_START;offset <= PWM_OUTPUT_REG_END;offset++)
    {
        fx_i2c(LED_ADDRESS,offset,0xFF);
    }
    fx_i2c(LED_ADDRESS,PWM_UPDATE_REG,0x00);
}
