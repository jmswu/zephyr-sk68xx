#include <stdio.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "sk68xx.h"

int main(void)
{

    sk68xx_init();

    printk("Hello world\n");

    union rgb_code color = SK68XX_RGB(5, 5, 5);

    for (;;)
    {
        sk68xx_update_rgb(color);
        sk68xx_reset();
        k_msleep(1000);
    }

    return 0;
}