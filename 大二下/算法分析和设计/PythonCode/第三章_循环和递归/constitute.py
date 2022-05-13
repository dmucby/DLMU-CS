def constitute():
    global a
    a = []
    global total
    total = 0
    for r in range(0, 100):
        a.append(0)
    n = int(input())
    r = int(input())
    a[0] = r
    comb(n, r)
    if n < r:
        return
    print(total)


def comb(n, r):
    global total
    for i in range(n, r-1, -1):
        a[r] = i
        if r > 1:
            comb(i - 1, r - 1)
        else:
            for j in range(a[0], 0, -1):
                print(a[j], end=" ")
            total += 1
            print(end="\n")


if __name__ == '__main__':
    constitute()
