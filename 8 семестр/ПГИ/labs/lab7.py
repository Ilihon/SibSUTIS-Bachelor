import io

from PIL import Image


# теоретически, если использовать 6 бит от каждого пикселя (2 бита на каждый цвет),
# то можно использовать ~25% от картинки
# (1000 * 833 * 6 / 8 / 1024) / 2380 = 0,2563
#  2380 kb * 0,2563 = 609 kb - максимальный размер информации

def main() -> int:
    image = Image.open("image TK 24 Bit.bmp")
    image_matrix = image.load()

    with open("text.txt", "r") as f:
        text = f.read()
        # print('Original text:', text)
        # for i in text:
            # print(i, ord(i), bin(ord(i)), chr(ord(i)))
        # посимвольно преобразовываем текст в двоичный код
        text_to_bits = ""
        for i in text:
            text_to_bits = text_to_bits + bin(ord(i))[2:].zfill(8)
            # print(bin(ord(i))[2:].zfill(8))
        # print(text_to_bits)
        # for i in text:
        #     print(i)
        print("Original text size:", len(text_to_bits), "bits")
        # print(bin(len(text_to_bits)))
        # print(text_to_bits_binary)

    bit_counter = 0
    text_bits = len(text_to_bits)
    for j in range(image.height):
        for i in range(image.width):
            # записываем 6 бит в rgb пикселя
            if bit_counter <= text_bits:
                image_pixel_rgba_list = list(image_matrix[i, j])
                # for v in range(len(image_pixel_rgba_list)):
                #     print(image_pixel_rgba_list[v], end=" ")
                # print(" - ", end="")
                for v in range(3):
                    if len(text_to_bits) != 2:
                        image_pixel_rgba_list[v] = ((image_pixel_rgba_list[v] >> 2) << 2) | int(text_to_bits[:2], 2)
                        text_to_bits = text_to_bits[2:]
                    # print(image_pixel_rgba_list[v], end=" ")
                # print()
                image_matrix[i, j] = tuple(image_pixel_rgba_list)
                bit_counter += 6
    image.save("steganography.bmp", "BMP")

    # декодирование файла
    new_image = Image.open("steganography.bmp")
    new_image_matrix = new_image.load()
    bits = ""
    result_text = ""
    bits_str = ""
    bit_counter = 0
    for j in range(new_image.height):
        for i in range(new_image.width):

            if bit_counter <= text_bits:
                image_pixel_rgba_list = list(new_image_matrix[i, j])
                bits = bits + bin(image_pixel_rgba_list[0] & 3)[2:].zfill(2)
                bits = bits + bin(image_pixel_rgba_list[1] & 3)[2:].zfill(2)
                bits = bits + bin(image_pixel_rgba_list[2] & 3)[2:].zfill(2)
                bits_str = bits_str + bits
                # print(bin(image_pixel_rgba_list[0] & 3), bin(image_pixel_rgba_list[1] & 3), bin(image_pixel_rgba_list[2] & 3),
                #       bits, bits[:8], int(bits[:8], 2), chr(int(bits[:8], 2)))
                # print(chr(int(bits[:8], 2)))
                if(len(bits) >= 8):
                    # print(bits[:8])
                    result_text = result_text + chr(int(bits[:8], 2))
                    bits = bits[8:]
                bit_counter += 6

    text_to_bits = ""
    for i in result_text:
        text_to_bits = text_to_bits + bin(ord(i))[2:].zfill(8)
    print("Decoded text size:", len(text_to_bits), "bits")
    # print(bits_str)
    # print(result_text)
    # print(len(text_to_bits))
    return 0


if __name__ == "__main__":
    exit(main())
