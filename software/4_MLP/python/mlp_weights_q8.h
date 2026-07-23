#ifndef MLP_WEIGHTS_H
#define MLP_WEIGHTS_H

#include <stdint.h>

#define MLP_INPUTS 2
#define MLP_HIDDEN 10
#define MLP_OUTPUTS 4
#define MLP_SHIFT 8
#define MLP_SCALE (1 << MLP_SHIFT)

static const int16_t mlp_w1[10][2] = {
    { -697, -11 },
    { -144, -98 },
    { -35, -620 },
    { -12, 72 },
    { -171, 595 },
    { 465, -151 },
    { 175, 142 },
    { 261, 410 },
    { -60, -46 },
    { 61, -21 }
};

static const int32_t mlp_b1[10] = { 212, 3, 238, -46, 216, 165, 6, 100, -82, -77 };

static const int16_t mlp_w2[4][10] = {
    { -364, -139, -273, 37, 155, 212, 133, 540, 106, -84 },
    { 381, -186, -407, 50, 397, 35, -254, -34, 214, 131 },
    { 388, 83, 398, 46, -269, -233, 40, -48, -51, 67 },
    { -367, -60, 247, 216, -252, 501, -170, -201, -104, -154 }
};

static const int32_t mlp_b2[4] = { 68, -87, -157, 176 };

#endif /* MLP_WEIGHTS_H */
