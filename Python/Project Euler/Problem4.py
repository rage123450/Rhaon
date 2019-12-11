max = 0
for i in range(900,1000):
    for j in range(900,1000):
        value = i*j
        if str(value) == str(value)[::-1]:
            if max < value:
                max = value
print(max)
