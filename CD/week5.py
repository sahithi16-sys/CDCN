def action(state,ch):
    if state in [0,1,3]:
        if ch=='c':
            return 3
        if ch=='d':
            return 4
    elif state==2:
        if ch=='$':
            return 100
    elif state==4:
        if ch in ['c','d','$']:
            return -3
    elif state==5:
        if ch=='$':
            return -1
    elif state==6:
        if ch in ['c','d','$']:
            return -2
    return 0

def goto(state,ch):
    if state==0 and ch=='C':
        return 1
    if state==0 and ch=='S':
        return 2
    if state==1 and ch=='C':
        return 5
    if state==3 and ch=='C':
        return 6
    return -1

def parse(inp):
    inp+="$"
    st=[0]
    i=0

    while i<len(inp):
        s = st[-1]
        ch = inp[i]
        act = action(s,ch)

        print(f"State : {s} , Input : {inp[i:]} : ",end="")

        if act==0:
            print("Action : ERROR!")
            print("\nString Rejected!")
            return
        elif act==100:
            print("Action : ACCEPT!")
            print("\nString Accepted")
            return
        elif act>0:
            print(f"Action : s{act}")
            st.append(act)
            i+=1
        elif act<0:
            p = -act
            if p==1:
                print("Action : r1 (S->CC)")
                length=2
            elif p==2:
                print("Action : r2(C->cC)")
                length=2
            elif p==3:
                print("Action : r3(C->d)")
                length=1

            for _ in range(length):
                st.pop()
            ns = goto(st[-1],"S" if p==1 else "C")

            if ns==-1:
                print("\nString Rejected!")
                return

            st.append(ns)

print("Grammar: ")
print("S->CC")
print("C->cC")
print("C->D")

str = input("\n Enter input string: ")

parse(str)