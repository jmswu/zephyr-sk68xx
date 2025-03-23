#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(led0)
#define LOW_TIME (2U)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static inline void sk68xx_code_reset()
{
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(85);
}

static inline void sk68xx_code_zero()
{
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(LOW_TIME);
}

static inline void sk68xx_code_one()
{
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 1);
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(LOW_TIME);
}
#define RGB(_g, _r, _b) \
    (union rgb_code)    \
    {                   \
        .val = {        \
            .g = _g,    \
            .r = _r,    \
            .b = _b     \
        }               \
    }

int main(void)
{

    int ret;
    if (!gpio_is_ready_dt(&led))
    {
        printk("GPIO not ready\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        printk("Can't config pin\n");
        return 0;
    }

    printk("Hello world\n");

    for (;;)
    {
        // gpio_pin_set_dt(&led, 1);
        // // k_msleep(100);
        // k_busy_wait(3);
        // gpio_pin_set_dt(&led, 0);
        // // k_msleep(100);
        // k_busy_wait(3);
        sk68xx_code_zero();
        sk68xx_code_one();
    }

    return 0;
}