star = ["***","* *","***"]

n = int(input())

def get_star(n):
    mat = []
    l = len(n)
    for i in range(l * 3):
        if i // 3 == 1:
            mat.append(n[i % l] + " " * l + n[i % l])
        else:
            mat.append(n[i % l] * 3)
    return list(mat)

k = 0
while n != 3:
    n = n // 3
    k += 1

for i in range(k):
    star = get_star(star)

for i in star:
    print(i)