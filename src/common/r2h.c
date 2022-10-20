#include "r2h.h"

#include <stdlib.h>

/* 转换成适合运算的Rgb类型的数据 */
void convertRgb(struct Rgb *rgb) {
    rgb->red = rgb->red / 255;
    rgb->green = rgb->green / 255;
    rgb->blue = rgb->blue / 255;
}

/* 转换成适合运算的Hsl类型的数据 */
void convertHsl(struct Hsl *hsl) {
    hsl->saturation = hsl->saturation * 0.01;
    hsl->lightness = hsl->lightness * 0.01;
}

/*========================================================*/
int cmp(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double *)b;

    return (arg1 > arg2) - (arg1 < arg2); // 可行的简写
}

/* 将rgb的三个数据放入数组进行比较，得出最大值max和最小值min */
void find_max_And_min(const struct Rgb *rgb, double *max, double *min) {
    double array[3] = {rgb-> red, rgb->green, rgb->blue};
    qsort(array, 3, sizeof(double), cmp);
    *min = array[0];
    *max = array[2];
}

/**
 * 将RGB转换成HSL
 * */
void rgbToHsl(struct Hsl *hsl, const struct Rgb *rgb) {
    double max, min;
    // 查找最小值、最大值
    find_max_And_min(rgb, &max, &min);

    double h;
    double l;
    double s;

    double r = rgb->red;
    double g = rgb->green;
    double b = rgb->blue;

    double dif_val = max - min; // max - min
    if (max == min) {
        h = 0;
    } else if ((max == r) && (g >= b)) {
        h = 60 * (g - b)/dif_val;
    } else if ((max == r) && (g < b)) {
        h = 60 * (g - b)/dif_val + 360;
    } else if (max == g) {
        h = 60 * (b - r)/dif_val + 120;
    } else {
        h = 60 * (r - g)/dif_val + 240;
    }

    l = 0.5 * (max + min);

    if ((l == 0) || (max == min)) {
        s = 0;
    } else if ((l > 0) && (l <= 0.5)) {
        s = dif_val / (2*l);
    } else {
        s = dif_val / (2 - 2*l);
    }

    hsl->hue = h;
    hsl->saturation = s;
    hsl->lightness = l;
}

/*========================================================*/
void convert0To1(double *value) {
    if (*value < 0) {
        *value = *value + 1;
    } else if (*value > 1) {
        *value = *value - 1;
    }
}

double colorC(const double *p, const double *q, const double *tC) {
    double tmp = *tC;
    double result;
    if (tmp < 1.0/6) {
        result = *p + ((*q - *p) * 6 * tmp);
    } else if ((tmp >= 1.0/6) && (tmp < 0.5)) {
        result = *q;
    } else if ((tmp >= 0.5) && (tmp < 2.0/3)) {
        result = *p + ((*q - *p) * 6 * (2.0/3 - tmp));
    } else {
        result = *p;
    }
    return result;
}

/**
 * 将HSL转化成RGB
 * */
void hslToRgb(struct Rgb *rgb, const struct Hsl *hsl) {
    double h = hsl->hue;
    double s = hsl->saturation;
    double l = hsl->lightness;

    double q;
    double p;
    double hK;

    double tR;
    double tG;
    double tB;

    if (l < 0.5) {
        q = l * (1+s);
    } else {
        q = l + s - (l*s);
    }

    p = 2*l - q;

    hK = h / 360;

    tR = hK + (1.0/3);
    tG = hK;
    tB = hK - (1.0/3);

    convert0To1(&tR);
    convert0To1(&tG);
    convert0To1(&tB);

    rgb->red = colorC(&p, &q, &tR);
    rgb->green = colorC(&p, &q, &tG);
    rgb->blue = colorC(&p, &q, &tB);
}