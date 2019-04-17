#!/urs/bin/env python3

import sys
import tkinter
from tkinter import Canvas


class CustomCanvas(Canvas):
    def __init__(self, height, width):
        pass


class Rectangle(object):
    def __init__(self, height, width, x, y):
        pass


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
