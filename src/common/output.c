#include "r2h.h"

#include <stdio.h>

void outputRgb(const struct Rgb *rgb) {
    // 输出形式： rgb(255, 254, 123)
    printf("rgb(%d, %d, %d)\n",
           (int)(rgb->red * 255 + 0.5),
           (int)(rgb->green * 255 + 0.5),
           (int)(rgb->blue * 255 + 0.5));
}

void outputHsl(const struct Hsl *hsl) {
    // 输出形式：hsl(123, 20%, 34%)
    printf("hsl(%.2lf, %.2lf%%, %.2lf%%)\n",
           (double)hsl->hue,
           (double)(hsl->saturation * 100),
           (double)(hsl->lightness * 100));
}

void outputHex(const struct Rgb *rgb) {
    // 输出形式：#ff23a3
    int r = (int)(rgb->red * 255 + 0.5);
    int g = (int)(rgb->green * 255 + 0.5);
    int b = (int)(rgb->blue * 255 + 0.5);
    printf("#%.2x%.2x%.2x", r, g, b);
}
