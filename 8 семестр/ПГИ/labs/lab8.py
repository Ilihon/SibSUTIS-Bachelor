import tkinter
from PIL import Image, ImageTk

window = tkinter.Tk()


def main():
    image = Image.open("image.pcx")
    print(image.getcolors())
    # image_resized = image.resize((image.width // 2, image.height // 2))
    photo = ImageTk.PhotoImage(image)
    canvas = tkinter.Canvas(window, height=image.height, width=image.width)
    canvas.create_image(0, 0, anchor='nw', image=photo)
    canvas.grid(row=0, column=0)
    window.mainloop()


if __name__ == "__main__":
    exit(main())
