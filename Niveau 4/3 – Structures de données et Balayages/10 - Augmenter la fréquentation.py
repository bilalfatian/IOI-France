import sys



def main():
    S=int(input())
    T=[[]]*S
    for i in range(S):
        D,F=map(int,sys.stdin.readline().split())
        T[i]=[D,F]
    T.sort()
    
    mn=T[0][0]
    r=T[0][1]
    mx=T[0][1]
    for i in range(1,S):
        r=r+T[i][1]
        if r/(i+1) >= mx :
            mx=r/(i+1)
            mn=T[i][0]
    
    print(mn)
main()
