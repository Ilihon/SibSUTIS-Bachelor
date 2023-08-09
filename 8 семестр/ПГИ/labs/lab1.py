from PIL import Image


def main() -> int:
    image = Image.open("image.bmp")
    image_matrix = image.load()
    print(f'Format: {image.format}\nSize: {image.size}\nColor-type:{image.mode}')
    print(image.info)
    for i in range(image.width):
        for j in range(image.height):
            # print(image_matrix[i, j], end="")
            color_mod = int(image_matrix[i, j][0] * 0.299 + image_matrix[i, j][1] * 0.587 + image_matrix[i, j][2] * 0.114)
            # print(color_mod)
            image_matrix[i, j] = (color_mod, color_mod, color_mod, 0)
            # print(f" - {image_matrix[i, j]}")
    image.save("image_greyscaled.bmp", "bmp")
    return 0


if __name__ == '__main__':
    exit(main())
