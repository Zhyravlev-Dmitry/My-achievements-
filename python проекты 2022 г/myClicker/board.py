import sys

from PIL import Image, ImageTk # $ pip install pillow
from tkinter import Canvas, ALL, NW, Button, SE, SW

from resources import *

class Board(Canvas):

    def __init__(self):
        super().__init__(
            width=BoardConst.BOARD_WIDTH, height=BoardConst.BOARD_HEIGHT,
            background=BoardConst.COLOUR, highlightthickness=0
        )
        self.ReadFile('rezults.txt')
        self.InitGame()
        self.pack()

    def ReadFile(self, file_str):
        file = open(file_str)
        self.capital = int(file.readline())
        self.click = int(file.readline())
        self.profit = int(file.readline())
        self.start_age = int(file.readline())
        self.enjoy = int(file.readline())
        self.cost_enjoy = int(file.readline())
        self.click_add_1 = int(file.readline())
        self.click_add_2 = int(file.readline())
        self.profit_add_1 = int(file.readline())
        self.profit_add_2 = int(file.readline())
        self.cost_click_add_1 = int(file.readline())
        self.cost_click_add_2 = int(file.readline())
        self.cost_profit_add_1 = int(file.readline())
        self.cost_profit_add_2 = int(file.readline())
        self.is_error = int(file.readline())
        self.total_capital = int(file.readline())
        self.timer = int(file.readline())
        file.close()
        self.age = self.start_age

    def InitGame(self):
        self.inGame = True

        self.cost_win = EconomicConst.WIN_COST
        self.result = 0

        self.LoadingGameResources()
        self.CreateObjects()

        self.bind_all("<space>", self.SpacePressed)
        self.bind("<Button-1>", self.SpacePressed)
        self.after(OtherConst.DELAY, self.GameLoop)


    def LoadingGameResources(self):
        # Подгружаем нужные изображения для игры.
        try:
            self.im_shop1 = Image.open("shop1.jpeg")
            self.shop1 = ImageTk.PhotoImage(self.im_shop1)
            self.im_shop2 = Image.open("shop2.jpeg")
            self.shop2 = ImageTk.PhotoImage(self.im_shop2)

        except IOError as e:
            print(e)
            sys.exit(1)

    def CreateDynamicText(self):
        if self.timer != 0:
            self.delete("t_capital")
            self.delete("t_profit")
            self.delete("t_age")
            self.delete("t_cost_enjoy")

        if self.is_error == 2:
            self.create_text(
                850, BoardConst.BOARD_HEIGHT - BoardConst.MARGIN_EDGE, text="Not enough money",
                tag="t_error", fill="firebrick", font="Verdana 12", anchor=SW)
        elif self.is_error == -1:
            self.delete("t_error")

        self.create_text(
            BoardConst.MARGIN_EDGE, 200, text="Capital: {0}".format(self.capital),
            tag="t_capital", fill="black", font="Verdana 14", anchor=NW)

        self.create_text(
            BoardConst.MARGIN_EDGE, 250, text="Profit: +{0} / click".format(self.click) +
                                   "\n          +{0} / tick".format(self.profit),
            tag="t_profit", fill="black", font="Verdana 14", anchor=NW)

        self.create_text(
            BoardConst.MARGIN_EDGE, 350, text="your age: {0}".format(self.age),
            tag="t_age", fill="gray", font="Verdana 10", anchor=NW)

        self.create_text(BoardConst.MARGIN_EDGE, BoardConst.BOARD_HEIGHT - BoardConst.MARGIN_EDGE,
                         text="cost: {0}".format(self.cost_enjoy),
                         tag="t_cost_enjoy", fill="black", font="Verdana 10", anchor=SW)

    def CreateObjects(self):

        #Создание объектов на холсте.

        self.CreateDynamicText()
        def BtnClickAdd_1():
            if (self.capital >= self.cost_click_add_1):
                self.click += self.click_add_1
                self.capital -= self.cost_click_add_1
            else:
                self.is_error = 1

        def BtnClickAdd_2():
            if (self.capital >= self.cost_click_add_2):
                self.click += self.click_add_2
                self.capital -= self.cost_click_add_2
            else:
                self.is_error = 1

        def BtnProfitAdd_1():
            if (self.capital >= self.cost_profit_add_1):
                self.profit += self.profit_add_1
                self.capital -= self.cost_profit_add_1
            else:
                self.is_error = 1

        def BtnProfitAdd_2():
            if (self.capital >= self.cost_profit_add_2):
                self.profit += self.profit_add_2
                self.capital -= self.cost_profit_add_2
            else:
                self.is_error = 1

        def BtnEnjoy():
            if (self.capital >= self.cost_enjoy):
                self.enjoy += 1
                self.capital -= self.cost_enjoy
                self.cost_enjoy += self.cost_click_add_1
            else:
                self.is_error = 1

        def BtnWin():
            if (self.capital >= self.cost_win):
                self.inGame = False
            else:
                self.is_error = 1

        def BtnReset():
            self.Reset()

        self.btn_win = Button(text=BoardConst.WIN_TITLE, height=3,
          width=40, command=BtnWin)
        self.btn_click_add_1 = Button(image=self.shop1, command=BtnClickAdd_1)
        self.btn_click_add_2 = Button(image=self.shop2, command=BtnClickAdd_2)
        self.btn_profit_add_1 = Button(image=self.shop1, command=BtnProfitAdd_1)
        self.btn_profit_add_2 = Button(image=self.shop2, command=BtnProfitAdd_2)
        self.btn_enjoy = Button(text="Enjoy life", command=BtnEnjoy)
        self.btn_reset = Button(text="reset", command=BtnReset)

        self.btn_win.place(x=300, y=40)
        RIGHT_IM_INDENT = 480
        RIGHT_IEXT_INDENT = 250

        bth_y = 100
        self.btn_click_add_1.place(x=BoardConst.BOARD_WIDTH - RIGHT_IM_INDENT, y=bth_y)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y+50,
            text="cost: {0}".format(self.cost_click_add_1), anchor=NW)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y+80,
                         text="max click: +{0}".format(self.click_add_1), anchor=NW)
        bth_y = 280
        self.btn_click_add_2.place(x=BoardConst.BOARD_WIDTH - RIGHT_IM_INDENT, y=bth_y)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y+50,
                         text="cost: {0}".format(self.cost_click_add_2), anchor=NW)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y+80,
                         text="max click: +{0}".format(self.click_add_2), anchor=NW)
        bth_y = 500
        self.btn_profit_add_1.place(x=BoardConst.BOARD_WIDTH - RIGHT_IM_INDENT, y=bth_y)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y + 50,
                         text="cost: {0}".format(self.cost_profit_add_1), anchor=NW)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y + 80,
                         text="profit: +{0} / tick".format(self.profit_add_1), anchor=NW)
        bth_y = 700
        self.btn_profit_add_2.place(x=BoardConst.BOARD_WIDTH - RIGHT_IM_INDENT, y=bth_y)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y + 50,
                         text="cost: {0}".format(self.cost_profit_add_2), anchor=NW)
        self.create_text(BoardConst.BOARD_WIDTH - RIGHT_IEXT_INDENT, bth_y + 80,
                         text="profit: +{0} / tick".format(self.profit_add_2), anchor=NW)

        self.btn_enjoy.place(x=BoardConst.MARGIN_EDGE, y=BoardConst.BOARD_HEIGHT - 80, anchor=SW,
                        height=80, width=400)

        self.btn_reset.place(x=BoardConst.BOARD_WIDTH - BoardConst.MARGIN_EDGE,
                        y=BoardConst.BOARD_HEIGHT - BoardConst.MARGIN_EDGE, anchor=SE,
                        height=50, width=300)

    def Reset(self):
        self.ReadFile('reset.txt')
        if self.timer == 0:
            self.delete(ALL)
            self.InitGame()
        else:
            self.timer = 1
            self.CreateDynamicText()

    def SpacePressed(self, event):
        self.capital += self.click
        self.total_capital += self.click
        print(self.capital)

    def GameLoop(self):
        self.timer += 1
        self.age = self.timer // (100 // OtherConst.SPEAD_GAME) + self.start_age
        if self.timer % 50 == 0:
            self.capital += self.profit
        if (self.age >= OtherConst.CRITICAL_AGE):
            self.inGame = False

        if (self.is_error > OtherConst.ERROR_DELAY):
            self.is_error = -1
        elif (self.is_error == -1):
            self.is_error = 0
        elif (self.is_error):
            self.is_error += 1

        self.CreateDynamicText()
        if self.inGame:
            self.after(OtherConst.DELAY, self.GameLoop)
        else:
            self.gameOver()

    def DeleteAll(self):
        self.delete(ALL)
        self.btn_win.destroy()
        self.btn_enjoy.destroy()
        self.btn_click_add_1.destroy()
        self.btn_click_add_2.destroy()
        self.btn_profit_add_1.destroy()
        self.btn_profit_add_2.destroy()

    def gameOver(self):
        self.DeleteAll()
        self.timer = 0

        if self.age < OtherConst.CRITICAL_AGE:
            self.create_text(self.winfo_width() / 2, self.winfo_height() / 2 - 100,
                         text="You have won at the age of {0}".format(self.age),
                         fill="black", font="Verdana 24")
        else:
            self.create_text(self.winfo_width() / 2, self.winfo_height() / 2 - 100,
                             text="You never retired :( ",
                             fill="black", font="Verdana 24")

        self.create_text(self.winfo_width() / 2, self.winfo_height() / 2 + 20,
                         text="For life you have earned {0}$".format(self.total_capital) +
                                                                     "\n     and enjoyed life {0} times".format(self.enjoy),
                         fill="black", font="Verdana 18")
        self.ReadFile('reset.txt')
