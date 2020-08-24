/*
The max-flow min-cut theorem is a network flow theorem. 
This theorem states that the maximum flow through any network from a given source to a given sink is exactly the sum of the edge weights that, 
if removed, would totally disconnect the source from the sink. 
In other words, for any network graph and a selected source and sink node,the max-flow from source to sink = the min-cut necessary (capacity) to separate source from sink.
 It is one kind of theorem. It has a strong proof. A graph has several min-cut but we have to choose those edges whose capacity summation will be minimum among all min-cut. 
 
 So here is a technique by which we can find the min-cut max-flow edges.
 That is using residual graph.First find the residual graph when flow is maximum.
 Now the graph is with assuming  maximum-flow.
 
 So,now applying dfs over source and found all reachable and non-reachable nodes from source.
 Now ,after this dfs.
 We will find those edges which are from the reachable node to the non-reachable node in the original graph.
*/


const int mx=5001;

long long graph[mx][mx]={0};
long long resgraph[mx][mx]={0};
int parent[mx];
bool visited[mx]={false};
int V;
long long mx_flow=0;

bool bfs(int s,int t)
{
    memset(visited,false,sizeof(visited));
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

/// find those nodes reachable through non-zero capacity edges from source in residual graph.
/// and marked them by visited array.
void dfs(int u)
{
    visited[u] = true;
    for (int v=0; v<V; v++)
    {
       if(resgraph[u][v] && !visited[v])
       {
           dfs(v);
       }
    }

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
    memset(visited,false,sizeof(visited));
    /// so , flow is now maximum 
    /// and residual graph has been built when flow is maximum
    /// then we will run our dfs now to find the nodes reachable from source.
    dfs(s);
    
///Print all edges that are from a reachable vertex(which are reachable from source by residual graph) to 
///non-reachable vertex(which are non-reachable from source by residual graph) using the original graph. 
    for (int i=1; i<=V; i++) 
    {
      for (int j=1; j<=V; j++) 
      {
         if (visited[i] && !visited[j] && graph[i][j]) 
         {
              cout<< i << "-" << j <<endl; 
         }
      }
    }
    
}
