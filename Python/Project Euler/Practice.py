N,M = list(map(int,input().split()))
arr = list(map(int,input().split()))

res = sum(arr)
for i in range(len(arr) - 2):
    for j in range(i + 1,len(arr) - 1):
        for k in range(j + 1,len(arr)):
            sum = arr[i] + arr[j] + arr[k]
            if sum <= M and M - sum < M - res:
                res = sum
print(res)