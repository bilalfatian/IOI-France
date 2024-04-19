def triInsertion(l,n):
   
    for idFin in range(len(l)):
        insere = l[idFin]
        ins=n[idFin]
        pos = idFin
        while pos > 0 and insere < l[pos-1]:
            l[pos] = l[pos-1]
            n[pos] = n[pos-1]
            pos -= 1
        l[pos] = insere
        n[pos] = ins

def mai():
    global d
    a=int(input())
    n=[]
    l=[]
    for i in range(a):
        m,f,d=map(int,input().split())
        if m==0:
            m=-1
        if f==0:
            f=-1
        n.append(m+f)
        l.append(d)
    triInsertion(l,n)
    b=2-sum(n)
    g=0
    if b==0:
        print(sum(l))
    elif b<0:
        i=0
        while b!=0 and len(n)>i:
            if n[i]>0:
                b=b+n[i]
                l[i]=0
            i=i+1
        if i>=len(n):
            print(-1)
        else:
            print(sum(l))
    elif b>0:
        i=0
        while b!=0 and len(n)>i:
            if n[i]<0:
                b=b+n[i]
                l[i]=0
            i=i+1
        if i>=len(n):
            print(-1)
        else:
            print(sum(l))
    
    
    
mai()
