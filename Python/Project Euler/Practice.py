N,M = map(int,input().split())
data = [ i + 1 for i in range(N)]
check = [False] * N
arr = []

def DFS(n):
    # 주어진 갯수만큼 채워지면 출력한다.
    if n == M:
        print(*arr)
        return

    # data 갯수만큼 순회한다.
    for i in range(N):
        # 이미 거쳐간 수라면 그냥 지나간다.
        if check[i]:
            continue

        # i번째는 거쳐갈거라서 True로 바꾼다.
        check[i] = True

        # 데이터를 넣는다.
        arr.append(data[i])

        # 현재의 i를 기준으로 가지치기를 시작
        DFS(n+1)

        # 최근에 넣은 데이터 하나 뺀다.
        arr.pop()

        # 거쳐갔다는 걸 취소한다.
        check[i] = False

DFS(0)
