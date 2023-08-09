from PIL import Image


smooth_coefficient = 15
colors_count_mode = 16#256


def count_delta(left, right):
    return sum([(x - y) ** 2 for x, y in zip(left, right)])


def find_palette(colors_palette: list):
    new_colors_palette = []
    # выбираем палитру из указанного количества цветов
    for i in range(colors_count_mode):
        # очищаем исходную палитру от схожих цветов в пределе установленного коэффицента сглаживания
        color = colors_palette.pop()[0]

        if (color[0] + 1, color[1], color[2]) in colors_palette:
            colors_palette.remove((color[0] + 1, color[1], color[2]))
        if (color[0] - 1, color[1], color[2]) in colors_palette:
            colors_palette.remove((color[0] - 1, color[1], color[2]))
        if (color[0], color[1] + 1, color[2]) in colors_palette:
            colors_palette.remove((color[0], color[1] + 1, color[2]))
        if (color[0], color[1] - 1, color[2]) in colors_palette:
            colors_palette.remove((color[0], color[1] - 1, color[2]))
        if (color[0], color[1], color[2]+1) in colors_palette:
            colors_palette.remove((color[0], color[1], color[2] + 1))
        if (color[0], color[1], color[2] - 1) in colors_palette:
            colors_palette.remove((color[0], color[1], color[2] - 1))
        for j in range(1, smooth_coefficient):
            for v in range(1, smooth_coefficient):
                for k in range(1, smooth_coefficient):
                    if (color[0] + j, color[1] + v, color[2] + k) in colors_palette:
                       colors_palette.remove((color[0] + j, color[1] + v, color[2] + k))
                    if (color[0] - j, color[1] - v, color[2] - k) in colors_palette:
                        colors_palette.remove((color[0] - j, color[1] - v, color[2] - k))
        new_colors_palette.append(color)
        # print(i)
    # print(new_colors_palette)
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

    colors_count = {}
    for color in pixels:
        colors_count[color] = colors_count[color] + 1 if color in colors_count else 1
    colors_count = list(colors_count.items())
    colors_count.sort(key=lambda x: x[1], reverse=True)
    # print(colors_count[:256])
    # return
    # print(colors_count)
    # print(len(colors_count))

    # smooth_colors(colors_count)
    color_palette = find_palette(colors_count)
    # print(colors_count[0:256])
    # print(len(color_palette))
    print(color_palette)
    # return
    # # print(color_palette)
    # print(pixels[0])
    # print(find_closest(color_palette, pixels[0]))
    pixels = [find_closest(color_palette, pixel) for pixel in pixels]
    # print(len(pixels))

    converted_image = Image.new('RGB', (image.width, image.height))
    converted_image.putdata(pixels)
    converted_image.save('image_16_another.pcx')
    converted_image.show()
    return 0


if __name__ == '__main__':
    exit(main())
