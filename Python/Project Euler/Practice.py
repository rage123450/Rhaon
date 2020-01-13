def adjacent(i):
    for j in range(0,i):
        # 새로운 퀸과 기존의 퀸이 같은 행에 있거나 대각선에 있을 경우
        if row[j] == row[i] or abs(row[j]-row[i]) == (i-j):
            return False
    return True
 
def dfs(i):
    global result
    if i == N:
        result += 1
    else:
        # N개의 퀸을 배치해야하므로 무조건 모든 행에 퀸이 들어가야한다.
        # 따라서 0열부터 N-1열까지 퀸을 놓는 방법을 for문을 통해 돌린다.
        for j in range(N):
            # i열에 있는 퀸의 행의 값 : row[i]
            row[i] = j
            # 유망한지(이전의 열로 인해 영향을 받는지) 검사하는 함수를 통해 걸러준다.
            if adjacent(i):
                dfs(i+1)
 
N = int(input())
row = [0]*N
result = 0
dfs(0)
print(result)