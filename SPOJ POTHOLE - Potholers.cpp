#include<bits/stdc++.h>

using namespace std;

/// Maximum Flow (Ford Fulkerson , Edmond's karp algorithm).
/// Time- O(VE^2).
/// Classical One ,Nice problem.

const int mx=201;

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


int main()
{
    int tc,t=0,n,u,v,j,i;
    cin>>tc;
    while(tc--)
    {
        cin>>n;
        mx_flow=0;
        t++;
        memset(resgraph,0,sizeof(resgraph));
        memset(parent,0,sizeof(parent));
        for( u=1;u<=n-1;u++)
        {
            cin>>i;
            for( j=1;j<=i;j++)
            {
                cin>>v;
                if(u==1||v==n) resgraph[u][v]=1;///the edge from the 1 and to reach n should be different (first and the last edge should be different).
                else resgraph[u][v]=100000;///others can be reused by more than 1 traveller.
            }
        }
        fordFulker(1,n);
        cout<<mx_flow<<endl;
    }
    return 0;
}
