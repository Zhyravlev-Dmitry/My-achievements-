GAME_NAME_EN = "Rat race"

class EconomicConst:
    WIN_COST = 800000 # выиграть можно, я проверял

class BoardConst:
    BOARD_WIDTH = 1600
    BOARD_HEIGHT = 1200
    COLOUR = "plum"
    WIN_TITLE = "Retire, cost: {}".format(EconomicConst.WIN_COST) + " (victory condition)"
    MARGIN_EDGE = 30

class OtherConst:
    DELAY = 10
    SPEAD_GAME = 1 # влияет только на возраст
    ERROR_DELAY = 100
    CRITICAL_AGE = 80