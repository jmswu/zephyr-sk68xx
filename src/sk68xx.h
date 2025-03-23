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

#define RGB(_r, _g, _b) \
    (union rgb_code)    \
    {                   \
        .val = {        \
            .b = _b,    \
            .r = _r,    \
            .g = _g,    \
        }               \
    }

    int sk68xx_init();
    int sk68xx_update_rgb(const union rgb_code color);
    int sk68xx_reset();

#ifdef __cplusplus
}
#endif