#!/urs/bin/env python3

import sys
import tkinter
from tkinter import Tk, Canvas

import rpack


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
        return (self.height == other.height and self.width == other.width) or
                (self.height == other.width and self.width == other.height)

    def __str__(self):
        return f"Rectangle with width of {self.width} and height of {self.height})"

    def __repr__(self):
        return f"<Rectangle(width={self.width}, height={self.height})>"

    def area(self):
        return self.width * self.height


def pack(allRect, canvasSize):
    rects = [(rect.width, rect.height) for rect in allRect]

    positions = rpack.pack(rects)

    for position, rect in zip(positions, allRect):
        rect.x = position[0]
        rect.y = position[1]


def main():
    if len(sys.argv) > 1:
        file_path = sys.argv[1]
    else:
        exit(1)

    height = 0
    width = 0
    packing_parameters = []

    with open(file_path) as f:
        canvas_size = tuple(f.readline().strip().split(","))
        packing_rects = [Rectangle(*line.strip().split(","), 0, 0) for line in f]

    pack(packing_rects, canvas_size)
    c = CustomCanvas(*canvas_size)

    c.draw(packing_rects)


if __name__ == "__main__":
    main()
