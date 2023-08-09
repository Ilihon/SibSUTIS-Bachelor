import random

from PIL import Image


def main() -> int:
    image = Image.open("image.bmp")
    image_matrix = image.load()
    print(f'Format: {image.format}\nSize: {image.size}\nColor-type:{image.mode}')
    print(image.info)
    frame_pixels = 15
    if image.width <= frame_pixels or image.height <= frame_pixels:
        frame_pixels = 0
    # верхние и нижние границы
    for i in range(image.width):
        for j in range(frame_pixels):
            image_matrix[i, j] = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 0)
            image_matrix[i, image.height - j - 1] = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 0)

    # левая и правая
    for i in range(image.height):
        for j in range(frame_pixels):
            image_matrix[j, i] = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 0)
            image_matrix[image.width - j - 1, i] = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 0)
    image.save("image_framed.bmp", "bmp")
    return 0


if __name__ == '__main__':
    exit(main())
