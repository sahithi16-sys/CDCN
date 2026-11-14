INF = float('inf')

def djikstra(n,graph,src):
    dist = [INF]*n
    prev=[-1]*n
    visited = [False]*n
    dist[src]=0

    for _ in range(n):
        u,best=-1,INF

        for v in range(n):
            if not visited[v] and dist[v]<best:
                u,best=v,dist[v]

        if u==-1:
            break
        visited[u]=True

        for v in range(n):
            w = graph[u][v]
            if w and not visited[v] and dist[u]+w<dist[v]:
                dist[v]=dist[u]+w
                prev[v]=u

    return dist,prev

def path(prev,v):
    p=[]
    while v!=-1:
        p.append(v)
        v=prev[v]
    return p[::-1]

n =  int(input("Enter number of nodes : "))
print("Enter cost adjacency matrix : ")
graph = [list(map(int,input().split())) for _ in range(n)]

src = int(input("Enter source node : "))

dist,prev = djikstra(n,graph,src)

print("Node   Distance    Path")

for i in range(n):
    if dist[i]==INF:
        print(f"{i:<6} {INF:<10} : No path")
    else:
        print(f"{i:<6} {dist[i]:<10} : {' -> '.join(map(str,path(prev,i)))}")