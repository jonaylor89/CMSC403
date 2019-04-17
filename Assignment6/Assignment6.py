#!/urs/bin/env python3

import sys
import tkinter
from tkinter import Tk, Canvas


class CustomCanvas(object):
    def __init__(self, height, width):
        master = Tk()
        self.canvas = Canvas(master, width=width, height=height)
        self.canvas.pack()

        master.mainloop()

class Rectangle(object):
    def __init__(self, height, width, x, y):
        self.height = height
        self.width = width
        self.x = x
        self.y = y


def pack(allRect, canvasSize):
    pass


def main():
    file_path = sys.argv[1]

    packing_parameters = []

    with open(file_path) as f:
        packing_parameters = [tuple(line.split(",")) for line in f] 

    # Print rectangles 


if __name__ == "__main__":
    main()
