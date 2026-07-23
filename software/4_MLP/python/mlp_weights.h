#ifndef MLP_WEIGHTS_H
#define MLP_WEIGHTS_H

#include <stdint.h>

#define MLP_INPUTS 2
#define MLP_HIDDEN 4
#define MLP_OUTPUTS 4
#define MLP_SHIFT 8
#define MLP_SCALE (1 << MLP_SHIFT)

static const int16_t mlp_w1[4][2] = {
    { 129, -565 },
    { -931, -105 },
    { 87, 867 },
    { -500, 265 }
};

static const int32_t mlp_b1[4] = { 347, 255, 322, 102 };

static const int16_t mlp_w2[4][4] = {
    { -228, -508, 598, -290 },
    { -362, 382, 315, 502 },
    { 147, 702, -571, 0 },
    { 518, -464, -332, -174 }
};

static const int32_t mlp_b2[4] = { 183, -337, -150, 305 };

#endif /* MLP_WEIGHTS_H */
