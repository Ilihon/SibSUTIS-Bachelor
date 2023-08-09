from PIL import Image


smooth_coefficient = 15
colors_count_mode = 16


def count_delta(left, right):
    return sum([(x - y) ** 2 for x, y in zip(left, right)])


def find_palette(image, pixels):
    colors = {}
    # находим повторения всех участвующих цветов сглаживая на +-3 оттенка
    for j in range(image.height):
        for i in range(image.width):
            pixel_access = list(pixels[i, j])
            smoothed_color = (pixel_access[0] >> 4 << 4, pixel_access[1] >> 4 << 4, pixel_access[2] >> 4 << 4)
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
    image = Image.open('image.bmp')
    # image.show()
    pixels = image.load()

    color_palette = find_palette(image, pixels)
    print(color_palette)

    pixels_new = []
    for j in range(image.height):
        for i in range(image.width):
            pixels_new.append(find_closest(color_palette, pixels[i,j]))
    # pixels = [find_closest(color_palette, pixel) for pixel in pixels]

    converted_image = Image.new('RGB', (image.width, image.height))
    converted_image.putdata(pixels_new)
    converted_image.save('image_16_another.bmp')
    converted_image.show()
    return 0


if __name__ == '__main__':
    exit(main())
