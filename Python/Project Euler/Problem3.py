n = max = 600851475143  
for x in range(2,int(max ** 0.5)):
    while n % x == 0:
        n = n / x
        print(x)
        break
