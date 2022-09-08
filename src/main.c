#include "r2h.h"

int main() {
    struct Rgb rgb1 = {99, 143, 156};
    convertRgb(&rgb1);
    struct Hsl hsl1;
    rgbToHsl(&hsl1, &rgb1);
    outputHsl(&hsl1);

    struct Hsl hsl2 = {193.68, 22.35, 50};
    convertHsl(&hsl2);
    struct Rgb rgb2;
    hslToRgb(&rgb2, &hsl2);
    outputRgb(&rgb2);
    outputHex(&rgb2);

    return 0;
}
