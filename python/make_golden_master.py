import trivia
import random


def make():
    for seed in range(0,100):
        print "Game for seed %s" % seed
        random.seed(seed)
        trivia.main()

if __name__ == "__main__":
    make()
