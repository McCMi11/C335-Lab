//#include <stdio.h>
#include <f3d_user_btn.h>
#include <f3d_systick.h>
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_delay.h>
#include <f3d_lcd_sd.h>
#include <glcdfont.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_usart.h>
#include <stm32f30x_spi.h>

int main(void) {
    f3d_led_init();
    f3d_user_btn_init();
    f3d_systick_init(100);
    f3d_uart_init();

    int led_n = 0;
    int delay_ms = 1;

    while (1) {
        // NOTE: delay_ms * (1000ms / 100) is milliseconds
        if (user_btn_read())
            delay_ms = 10;
        else
            delay_ms = 1;

        Delay(delay_ms);
        f3d_led_on(led_n);
        Delay(delay_ms);
        f3d_led_all_off();
        led_n = (led_n + 1) % 8;
    }
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    while (1);
}
#endif
