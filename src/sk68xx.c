#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "sk68xx.h"

#define LED_NODE DT_ALIAS(led0)
#define SK68xx_T0L (2U)
#define SK68xx_T1L (2U)
#define SK68xx_Trst (85U)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static inline void sk68xx_code_zero()
{
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(SK68xx_T0L);
}

static inline void sk68xx_code_one()
{
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(SK68xx_T1L);
}

int sk68xx_init()
{
    int ret;
    if (!gpio_is_ready_dt(&led))
    {
        return -EXIT_FAILURE;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return -EXIT_FAILURE;
    }
}

int sk68xx_update_rgb(const union rgb_code rgb)
{
    int index = 24;
    while (index)
    {
        if (rgb.data & (1 << --index))
        {
            sk68xx_code_one();
        }
        else
        {
            sk68xx_code_zero();
        }
    }

    return 0;
}

int sk68xx_reset()
{
    int ret = gpio_pin_set_dt(&led, 0);
    k_busy_wait(SK68xx_Trst);
    return ret;
}