#ifndef RGB_R2H_H
#define RGB_R2H_H

struct Rgb {
    double red;
    double green;
    double blue;
};

struct Hsl {
    double hue; // 色相
    double saturation; // 饱和度
    double lightness; // 亮度
};

/**
 * 例如：将rgb(255, 255, 0)转换成rgb(1, 0, 0)，以便于参与rgb与hsl的转换
 */
void convertRgb(struct Rgb *rgb);

/**
 * 例如：将hsl(193.68, 22.35, 50)转换成hsl(193.68, 0.2235, 0.5)
 */
void convertHsl(struct Hsl *hsl);

/**
 * 将RGB类型的数据转换成HSL类型的数据
 */
void rgbToHsl(struct Hsl *hsl, const struct Rgb *rgb);

/**
 *  将HSL类型的数据转换成RGB类型的数据
 */
void hslToRgb(struct Rgb *rgb, const struct Hsl *hsl);

// 将rgb、hsl的数据进行输出
void outputRgb(const struct Rgb *rgb);
void outputHsl(const struct Hsl *hsl);
void outputHex(const struct Rgb *rgb);

#endif //RGB_R2H_H
