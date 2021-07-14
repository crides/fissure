from kicaq import *
import sys

board = Board(sys.argv[1])
def sub(a, b):
    return a[0] - b[0], a[1] - b[1]

top = sub(board.pos("K9") , board.pos("J3"))
bot = sub(board.pos("J4") , board.pos("K19"))
print(top, bot)
print(top[0] + bot[0], top[1] + bot[1])
