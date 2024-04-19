def main():
    nb=int(input())
    l=[[]]*nb
    for i in range(nb):
        l[i]=list(map(int,input().split()))
    l.sort()
    s=l[0][1]-l[0][0]
    j=1
    for i in range(1,nb):
        if l[i][0]>=l[j-1][1]:
            s+=l[i][1]-l[i][0]
            j=i+1
        elif l[i][0]<l[j-1][1] and l[i][1]>l[j-1][1]:
            s+=l[i][1]-l[j-1][1]
            j=i+1
    
    print(s)     
main()
