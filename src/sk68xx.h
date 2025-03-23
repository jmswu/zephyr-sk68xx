#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

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

#define SK68XX_RGB(_r, _g, _b) \
    (union rgb_code)           \
    {                          \
        .val = {               \
            .b = _b,           \
            .r = _r,           \
            .g = _g,           \
        }                      \
    }

    /**
     * @brief Setup thhe sk68xx gpio
     *
     * @return int Success is 0, others are failed
     */
    int sk68xx_init();

    /**
     * @brief Update sk68xx LED color
     *
     * @param color RGB color
     * @return int Success is 0, others are failed
     */
    int sk68xx_update_rgb(const union rgb_code color);

    /**
     * @brief Rest code
     *
     * After sending the LED color, we need to send the reset signal to the LED
     * to the LED can show the color, and be ready for next command.
     *
     * @return int
     */
    int sk68xx_reset();

#ifdef __cplusplus
}
#endif