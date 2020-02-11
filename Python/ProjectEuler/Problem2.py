t = []
t.append(1)
t.append(2)

idx0 = 0
idx1 = 1
sum = 0
while True:
    t.append(t[idx0] + t[idx1])
    idx0+=1
    idx1+=1
    if t[idx1] > 4000000:
        break
#print(t)
for x in t:
    if x%2==0:
        sum+=x
print(sum)



    

