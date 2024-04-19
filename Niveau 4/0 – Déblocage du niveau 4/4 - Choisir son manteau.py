
N = int(input())
manteaux = [tuple(map(int, input().split())) for i in range(N)]
manteaux = dict(enumerate(sorted(manteaux, key=lambda x: (x[0], -x[1]))))
m2 = sorted(manteaux, key=lambda x: (-manteaux[x][1], manteaux[x][0]))
p2 = {m: i for i, m in enumerate(m2)}
print(max(N - i - p2[i] - 1 for i in range(N)))


#z = [tuple(map(int,input().split()))for i in range(int(input()))]
#z.sort(key=lambda x:x[1]-x[0],reverse=1)
#qgr = 0
#while qgr<len(z)/2:
#   mag = len(z)
#   a,*b = z
#   z = [i for i in b if not (i[0]>=a[0] and i[1]<=a[1])]
#   if mag-len(z)>qgr: qgr=mag-len(z)
#print(qgr-1)
