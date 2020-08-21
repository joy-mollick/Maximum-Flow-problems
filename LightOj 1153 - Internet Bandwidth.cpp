
/// Maximum Flow (Ford Fulkerson , Edmond's karp algorithm).

#include<bits/stdc++.h>

using namespace std;

const int mx=101;

int graph[mx][mx]={0};
int resgraph[mx][mx]={0};
int parent[mx];

int mx_flow=0;

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
        int path_flow=INT_MAX;
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

int main()

{
    int tc,t,total,V;
    cin>>tc;
    for(t=1;t<=tc;t++)
    {
    mx_flow=0;
    memset(graph,0,sizeof(graph));
    memset(resgraph,0,sizeof(resgraph));
    memset(parent,-1,sizeof(parent));
    int cst,u,v;
    int source,sink;
    cin>>V;
    cin>>source>>sink>>total;
    while(total--)
    {
    cin>>u>>v>>cst;
    graph[u][v]+=cst;
    graph[v][u]+=cst;
    }
    fordFulker(source,sink);
    cout<<"Case "<<t<<": ";
    cout<<mx_flow<<endl;
    }
    return 0;
}
