from PIL import Image
import numpy as np

def main() -> int:
    # image = Image.open("image.bmp")
    # image_matrix = image.load()
    # print(f'Format: {image.format}\nSize: {image.size}\nColor-type:{image.mode}')
    # print(image.info)
    #
    # # print(type(image_matrix))
    # # np_matrix = numpy.asarray(image)
    # # print(np_matrix)
    #
    # rotated_matrix = []
    # for i in range(image.width):
    #     rotated_matrix.extend([image_matrix[image.width - i - 1, image.height - j -1] for j in range(image.height)])
    # rotated_image = Image.new('RGBA', (image.height, image.width))
    # rotated_image.putdata(rotated_matrix)
    #
    # rotated_image.save("image_rotated.bmp", "bmp")
    # return 0

    img = Image.open("image.bmp")
    img_matrix = np.array(img.convert('RGBA'))
    # img_matrix = np.rot90(img_matrix)
    img_matrix = img_matrix.transpose((1, 0, 2))
    # img_matrix = img_matrix.transpose((1, 0, 2))
    # img_matrix = img_matrix.transpose((1, 0, 2))
    img_matrix = img_matrix[::-1]

    rotated_image = Image.fromarray(img_matrix, 'RGBA')
    # rotated_image.save("image_rotated.bmp", "bmp")
    rotated_image.show()


if __name__ == '__main__':
    exit(main())
