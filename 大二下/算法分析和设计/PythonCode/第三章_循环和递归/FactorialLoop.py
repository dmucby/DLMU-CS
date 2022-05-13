def factorialLoop(nn):
    S = 1.0000
    sign = 1
    t = 1
    for i in range(2, nn):
        sign = -sign
        t = t * ((2 * i - 2) * (2 * i - 1))
        S += sign / t
    return S


if __name__ == '__main__':
    n = int(input())
    print(factorialLoop(n))
