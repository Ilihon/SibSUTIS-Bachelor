from PIL import Image


def main() -> int:
    image = Image.open('image.bmp')
    image_matrix = image.load()
    print(f'Original: {image.size} \nEnter multiplier:')
    scaling_factor = float(input())
    scaled_width = round(image.width * scaling_factor)
    scaled_height = round(image.height * scaling_factor)
    scaled_image = Image.new('RGBA', (scaled_width, scaled_height))
    print(f'Scaled: {scaled_image.size}')
    scaled_matrix = [image_matrix[j // scaling_factor, i // scaling_factor] for i in range(scaled_height) for j in range(scaled_width)]
    scaled_image.putdata(scaled_matrix)
    scaled_image.save('image_scaled.bmp')
    scaled_image.show()
    return 0


if __name__ == '__main__':
    exit(main())
