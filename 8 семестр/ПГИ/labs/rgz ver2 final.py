from PIL import Image


smooth_coefficient = 15
colors_count_mode = 256


def count_delta(left, right):
    return sum([(x - y) ** 2 for x, y in zip(left, right)])


def find_palette(pixels):
    colors = {}
    # находим повторения всех участвующих цветов сглаживая на +-3 оттенка
    for color in pixels:
        smoothed_color = (color[0] >> 4 << 4, color[1] >> 4 << 4, color[2] >> 4 << 4)
        colors[smoothed_color] = colors[smoothed_color] + 1 if smoothed_color in colors else 1
    colors = list(colors.items())
    colors.sort(key=lambda x: x[1], reverse=True)

    new_colors_palette = []
    for i in range(colors_count_mode):
        color = colors.pop()[0]
        new_colors_palette.append(color)
    return new_colors_palette


def find_closest(color_palette, color):
    res = (0, 0, 0)
    for i in color_palette:
        # print(count_delta(res, color), count_delta(i, color))
        if count_delta(res, color) > count_delta(i, color):
            res = i
    return res


def main() -> int:
    image = Image.open('image.pcx')
    image.show()
    pixels = image.getdata()

    color_palette = find_palette(pixels)
    print(color_palette)
    pixels = [find_closest(color_palette, pixel) for pixel in pixels]

    converted_image = Image.new('RGB', (image.width, image.height))
    converted_image.putdata(pixels)
    converted_image.save('image_256_another.pcx')
    converted_image.show()
    return 0


if __name__ == '__main__':
    exit(main())
