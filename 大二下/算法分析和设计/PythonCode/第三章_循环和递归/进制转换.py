def conversion(n):
    a = []
    while n >= 1:
        s = n % 2
        n = n / 2
        a.append(s)
    a.reverse()
    print(a)

if __name__ == '__main__':
    n = int(input())
    conversion(n)