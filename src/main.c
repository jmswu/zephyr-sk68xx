#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

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
        gpio_pin_set_dt(&led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&led, 0);
        k_msleep(100);
    }

    return 0;
}