from functools import reduce

def mul(arr):
    return reduce(lambda x,y:x*y,arr)

a = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
#a = [2,3,4,5,6,7,8,9,10]
b = []

for x in a:
    for y in b:
        if x%y==0:
            x/=y    
    if x==1:
        pass
    else:
        b.append(x)
print(mul(b))

