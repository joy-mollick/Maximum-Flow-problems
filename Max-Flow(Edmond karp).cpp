/// Maximum Flow (Ford Fulkerson , Edmond's karp algorithm).
/// Time- O(VE^2).

const int mx=5001;

long long graph[mx][mx]={0};
long long resgraph[mx][mx]={0};
int parent[mx];

long long mx_flow=0;

bool bfs(int s,int t)
{
    bool visited[mx]={false};
    queue<int>q;
    q.push(s);
    visited[s]=true;
    parent[s]=-1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=0;v<mx;v++)
        {
            if(visited[v]==false && resgraph[u][v]>0)
            {
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    return (visited[t]==true);
}

void fordFulker(int s,int t)
{
    int v;
    for(int u=0;u<mx;u++)
    {
        for(int v=0;v<mx;v++)
        {
            resgraph[u][v]=graph[u][v];
        }
    }
    while(bfs(s,t)==true)
    {
        long long path_flow=INT_MAX;
        for(v=t;v!=s;v=parent[v])
        {
            int u=parent[v];
            path_flow=min(path_flow,resgraph[u][v]);
        }
        for(v=t;v!=s;v=parent[v])
        {
            int u=parent[v];
            resgraph[u][v]-=path_flow;
            resgraph[v][u]+=path_flow;
        }
        //cout<<path_flow<<endl;
        mx_flow=mx_flow+path_flow;
    }
}
