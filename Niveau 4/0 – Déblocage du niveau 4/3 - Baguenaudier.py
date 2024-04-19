def main():
    global u
    nbP=int(input())
    plateau=['_']*nbP
    def supp(i):
        if i==0:
            plateau[i]=' '
            print(i+1)
        elif plateau[i-1]=='_':
            for u in range(i-2,-1,-1):
                if plateau[u]=='_':
                    supp(u)
            plateau[i]=' '
            print(i+1)
        else:
            remplie(i-1,i)
            supp(i)
    def remplie(x,i):
        if x==0 :
            plateau[x]='_'
            print(x+1)
        elif plateau[x-1]=='_':
            for r in range(x-2,-1,-1):
                if plateau[r]=='_':
                    supp(r)
            plateau[x]='_'
            print(x+1)
            if x-1>=0:
                supp(x-1)
        else:
            if x-1>=0:
                remplie(x-1,i)
    for v in range(1,nbP+1):
        if plateau[nbP-v]=='_':
            supp(nbP-v)
main()
