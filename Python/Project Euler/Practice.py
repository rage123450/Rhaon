n = int(input())
arr = []
for _ in range(n):
    arr.append(list(map(int,input().split())))

len = len(arr)
rank = [1] * len

for i in range(len):
    for x in range(len):
        if i == x:
            continue
        if arr[i][0] < arr[x][0] and arr[i][1] < arr[x][1]:
            rank[i]+=1

for i in rank:
    print(i,end=' ')