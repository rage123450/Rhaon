def Func(a,b):
    len = b - a

    if len == 1 or len == 2:
        return len
    idx = 2
    while True:
        if len <= idx ** 2:
            if len <= (idx ** 2) - idx:
                return 2 * (idx - 1)
            else:
                return 2 * idx - 1
        idx+=1

tlist = [list(map(int,input().split())) for _ in range(int(input()))]

for a,b in tlist:
    print(Func(a,b))