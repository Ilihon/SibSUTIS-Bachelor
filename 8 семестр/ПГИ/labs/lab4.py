import tkinter
from PIL import Image, ImageTk


window = tkinter.Tk()


def main() -> int:
    image_16 = Image.open("image 16.bmp")
    print(image_16.getcolors())
    image_resized_16 = image_16.resize((image_16.width // 2, image_16.height // 2))
    photo_16 = ImageTk.PhotoImage(image_resized_16)
    canvas_16 = tkinter.Canvas(window, height=image_resized_16.height, width=image_resized_16.width)
    canvas_16.create_image(0, 0, anchor='nw', image=photo_16)
    canvas_16.grid(row=0, column=0)

    image_256 = Image.open("image 256.bmp")
    image_resized_256 = image_256.resize((image_256.width // 2, image_256.height // 2))
    photo_256 = ImageTk.PhotoImage(image_resized_256)
    canvas_256 = tkinter.Canvas(window, height=image_resized_256.height, width=image_resized_256.width)
    canvas_256.create_image(0, 0, anchor='nw', image=photo_256)
    canvas_256.grid(row=0, column=1)

    image_true_color = Image.open("image.bmp")
    image_resized_true_color = image_true_color.resize((image_true_color.width // 2, image_true_color.height // 2))
    photo_true_color = ImageTk.PhotoImage(image_resized_true_color)
    canvas_true_color = tkinter.Canvas(window, height=image_resized_true_color.height, width=image_resized_true_color.width)
    canvas_true_color.create_image(0, 0, anchor='nw', image=photo_true_color)
    canvas_true_color.grid(row=0, column=2)

    window.mainloop()
    return 0


if __name__ == '__main__':
    exit(main())
