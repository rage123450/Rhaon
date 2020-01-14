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
            cal(num + num_list[idx],idx + 1,add - 1,sub,mul,div)
        if sub:
            cal(num - num_list[idx],idx + 1,add,sub - 1,mul,div)
        if mul:
            cal(num * num_list[idx],idx + 1,add,sub,mul - 1,div)
        if div:
            cal(int(num / num_list[idx]),idx + 1,add,sub,mul,div - 1)

maxv = -sys.maxsize - 1
minv = sys.maxsize

n = int(input().strip())
num_list = list(map(int,input().strip().split()))

a,b,c,d = map(int,input().strip().split())

cal(num_list[0],1,a,b,c,d)

print(maxv)
print(minv)