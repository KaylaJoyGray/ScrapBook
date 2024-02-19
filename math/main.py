# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

w = 1920.0
h = 1080.0


def compat(size):
    if size == 0:
        return False

    if w % size == 0 and h % size == 0:
        return True
    return False


min: int = int(min(w, h))


def find_sizes():
    for i in range(min):
        if compat(i):
            print(i, ": ", "c: ", w / i, ", r: ", h / i)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    find_sizes()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
