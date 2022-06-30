from tkinter import Frame
from resources import *
from board import Board


class GameName(Frame):

    def __init__(self):
        super().__init__()
        self.master.title(GAME_NAME_EN)
        self.board = Board()
        self.pack()
