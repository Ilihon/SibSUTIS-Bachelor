from PIL import Image


def main() -> int:
    image = Image.open('image.bmp')
    logo = Image.open('logo.png')
    image_matrix = image.load()
    logo_matrix = logo.load()


    # logo.show()
    # print(image.width, image.height)
    # print(logo.width, logo.height)

    for j in range(logo.height):
        for i in range(logo.width):

            # print(logo_matrix[i,j])
            # print(i, image.height - logo.height - j - 1)
            # print(image_matrix[i, image.height - logo.height - j - 1])

            logo_pixel_rgba_list = list(logo_matrix[i, j])

            if logo_pixel_rgba_list.count(0) == len(logo_pixel_rgba_list):
                continue

            image_pixel_rgba_list = list(image_matrix[i, image.height - logo.height + j])
            # print(image.height - logo.height - j)
            for v in range(len(logo_pixel_rgba_list)):
                image_pixel_rgba_list[v] = int(image_pixel_rgba_list[v] * 0.8) + int(logo_pixel_rgba_list[v] * 0.2)

            # print(image_pixel_rgba_list)
            image_matrix[i, image.height - logo.height + j] = tuple(image_pixel_rgba_list)

    image.save("image_watermarked.bmp", "bmp")
    image.show()
    return 0


if __name__ == '__main__':
    exit(main())
