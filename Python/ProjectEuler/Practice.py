import sys
input = sys.stdin.readline

def cal(num,idx,add,sub,mul,div):
    global n,maxv,minv
    if idx == n:
        maxv = max(num,maxv)
        minv = min(num,minv)
        return
    else:
        if add:
            cal(num + data[idx],idx + 1,add - 1,sub,mul,div)
            pass
        if sub:
            cal(num - data[idx],idx + 1,add,sub - 1,mul,div)
            pass
        if mul:
            cal(num * data[idx],idx + 1,add,sub,mul - 1,div)
            pass
        if div:
            cal(int(num / data[idx]),idx + 1,add,sub,mul,div - 1)
            pass

maxv = -sys.maxsize - 1
minv = sys.maxsize

n = int(input().strip())
data = list(map(int,input().strip().split()))

add,sub,mul,div = map(int,input().strip().split())

cal(data[0],1,add,sub,mul,div)

print(maxv)
print(minv)