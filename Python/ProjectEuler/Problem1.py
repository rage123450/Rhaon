#a = list(filter(lambda x:x % 3 == 0 or x % 5 == 0, list(range(1,1000))))
#sum = 0
#for i in a:
#    sum+=i
#print(sum)

total = sum([x for x in range(1,1000) if x % 3 == 0 or x % 5 == 0])
print(total)
