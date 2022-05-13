def perfectNumber():
    for i in range(1000):
        s = i
        for j in range(1,i):
            if i % j == 0:
                s -= j
        if s == 0 and i != 0:
            print(i)


if __name__ == '__main__':
    perfectNumber()
