#include <stdio.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(led0)
#define SK68xx_T0L (2U)
#define SK68xx_T1L (2U)
#define SK68xx_Trst (85U)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static inline void sk68xx_code_reset()
{
    gpio_pin_set_dt(&led, 0);
    k_busy_wait(SK68xx_Trst);
}

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

union rgb_code
{
    struct
    {
        uint8_t b;
        uint8_t r;
        uint8_t g;
        uint8_t not_used;
    } val;
    uint32_t data;
};

#define RGB(_r, _g, _b) \
    (union rgb_code)    \
    {                   \
        .val = {        \
            .b = _b,    \
            .r = _r,    \
            .g = _g,    \
        }               \
    }

static inline void sk68xx_color(const union rgb_code rgb)
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

    union rgb_code color = RGB(10, 0, 0);

    for (;;)
    {
        sk68xx_color(color);
        sk68xx_code_reset();
    }

    return 0;
}