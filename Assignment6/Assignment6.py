#!/urs/bin/env python3

import sys
import tkinter
from tkinter import Tk, Canvas


class CustomCanvas(object):
    def __init__(self, height, width):

        self.rects: List[Rectangle] = []

        self.master = Tk()
        self.canvas = Canvas(self.master, width=width, height=height)
        self.canvas.pack()


    def draw(self, all_rects):
        for rect in all_rects:
            self.rects.append(
                self.canvas.create_rectangle(
                    rect.x,
                    rect.y,
                    rect.x + rect.width,
                    rect.y + rect.height,
                    outline="black",
                    fill="white",
                )
            )

        self.master.mainloop()

class Rectangle(object):
    def __init__(self, height, width, x, y):
        self.height: int = int(height)
        self.width: int = int(width)
        self.x: int = int(x)
        self.y: int = int(y)

    def __eq__(self, other):
        return self.height == other.height and self.width == other.width


def pack(allRect, canvasSize):
    pass


def main():
    if len(sys.argv) > 1:
        file_path = sys.argv[1]
    else:
        exit(1)

    height = 0
    width = 0
    packing_parameters = []

    with open(file_path) as f:
        canvas_size = tuple(f.readline().split(","))
        packing_rects = [Rectangle(*line.split(","), 0, 0) for line in f]

    pack(packing_rects, canvas_size)
    c = CustomCanvas(*canvas_size)

    c.draw(packing_rects)


if __name__ == "__main__":
    main()
