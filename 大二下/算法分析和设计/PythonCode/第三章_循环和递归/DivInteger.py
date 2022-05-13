def divider(n, m):
    if n == 1 or m == 1:
        return 1
    elif n < m:
        return divider(n, n)
    elif n == m:
        return divider(n, n - 1) + 1
    else:
        return divider(n - m, m) + divider(n, m - 1)



if __name__ == '__main__':
    nn = input()
    nn = int(nn)
    print(divider(nn, nn))
