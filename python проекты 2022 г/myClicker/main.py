from tkinter import Tk
from game_name import GameName


def Safe(board):
    safe_file = open('rezults.txt', "w")
    safe_file.write(str(board.capital) + '\n' +
                    str(board.click) + '\n' +
                    str(board.profit) + '\n' +
                    str(board.start_age) + '\n' +
                    str(board.enjoy) + '\n' +
                    str(board.cost_enjoy) + '\n' +
                    str(board.click_add_1) + '\n' +
                    str(board.click_add_2) + '\n' +
                    str(board.profit_add_1) + '\n' +
                    str(board.profit_add_2) + '\n' +
                    str(board.cost_click_add_1) + '\n' +
                    str(board.cost_click_add_2) + '\n' +
                    str(board.cost_profit_add_1) + '\n' +
                    str(board.cost_profit_add_2) + '\n' +
                    str(0) + '\n' +
                    str(board.total_capital) + '\n' +
                    str(board.timer) + '\n')
    safe_file.close()

def main():
    root = Tk()
    game = GameName()
    root.mainloop()
    Safe(game.board)

if __name__ == '__main__':
    main()
