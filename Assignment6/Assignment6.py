#!/urs/bin/env python3

import sys
import tkinter
from tkinter import Tk, Canvas


class CustomCanvas(object):
    def __init__(self, height, width):

        self.rects = []

        master = Tk()
        self.canvas = Canvas(master, width=width, height=height)
        self.canvas.pack()

        master.mainloop()

    def show(self, all_rects):
        for rect in all_rects:
            self.rects.append(
                self.canvas.create_rectangle(
                    rect.x, rect.y, rect.x + rect.width, rect.y + rect.height
                )
            )


class Rectangle(object):
    def __init__(self, height, width, x, y):
        self.height = height
        self.width = width
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.height == other.height and self.width == other.width


def pack(allRect, canvasSize):
    pass


def main():
    file_path = sys.argv[1]

    height = 0
    width = 0
    packing_parameters = []

    with open(file_path) as f:
        canvas_size = tuple(f[:2])
        packing_rects = [Rectangle(*line.split(",")) for line in f[2:]]

    pack(packing_rects, canvas_size)
    c = CustomCanvas(*canvas_size)


if __name__ == "__main__":
    main()
