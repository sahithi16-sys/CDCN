first = {}
follow = {}

def firstOf(s,k):
    r = set()
    eps=True

    while k<len(s) and eps:
        X = s[k]
        if not X.isupper():
            r.add(X)
            eps=False
        else:
            r.update(first[X])
            r.discard('#')
            eps = '#' in first[X]

        k+=1
    return r,eps

n = int(input("Enter number of productions : "))
lhs = []
rhs=[]

for i in range(n):
    p = input().strip()
    A = p[0]
    parts = p[2:].split('|')

    for part in parts:
        lhs.append(A)
        rhs.append(part)

for A in lhs:
    first[A] = set()
    follow[A] = set()

change = True

while change:
    change = False

    for i in range(len(lhs)):
        A=lhs[i]
        s=rhs[i]
        r,eps = firstOf(s,0)

        if eps:
            r.add('#')

        for c in r:
            if c not in first[A]:
                first[A].add(c)
                change=True

follow[lhs[0]].add('$')

change = True

while change:
    change = False

    for i in range(len(lhs)):
        A = lhs[i]
        s = rhs[i]
        for k in range(len(s)):
            B = s[k]

            if not B.isupper():
                continue

            r,eps = firstOf(s,k+1)
            if eps:
                r.update(follow[A])

            for c in r:
                if c not in follow[B]:
                    follow[B].add(c)
                    change=True

nt = set(lhs)

for A in sorted(nt):
    print("FIRST(" + A + ") = {",*sorted(first[A]), "}")

print()

for A in sorted(nt):
    print("FOLLOW(" + A + ") = {",*sorted(follow[A]), "}")