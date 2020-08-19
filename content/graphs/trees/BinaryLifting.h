
/**
 * Description: Binary Lifting / LCA / tree distance (feat. depth)
 * Time: $O(\log n)$ for all ops.
 * Status: Tested (on one problem)
*/

vector<int> depth;
vector<vector<int>> edges;
vector<vector<int>> lift;

void dfs(int cur, int par){
    if(cur!=par){
        lift[cur][0] = par;
        for(int i = 1; i < lift[cur].size(); i++){
            if(lift[cur][i-1] == -1 || lift[lift[cur][i-1]][i-1] == -1)break;
            lift[cur][i] = lift[lift[cur][i-1]][i-1];
        }
    }
    depth[cur] = depth[par]+1;
    for(int child:edges[cur]){
        if(child==par)continue;
        dfs(child, cur);
    }
}

int blift(int u, int amt){
    for(int bit = lift[0].size()-1; bit>=0; bit--){
        if(amt&(1<<bit))u = lift[u][bit];
        if(u==-1)return u;
    }
    return u;
}


int lca(int u, int v){
    if(depth[u]>depth[v])swap(u, v);
    v = blift(v, depth[v]-depth[u]);

    for(int bit = lift[0].size()-1; bit>=0; bit--){
        if(lift[u][bit]==lift[v][bit])continue;
        u = blift(u, 1<<bit);
        v = blift(v, 1<<bit);
    }
    if(u!=v) return lift[u][0];
    return u;
}

inline int dist(int u, int v){
    return depth[v]+depth[u]-2*depth[lca(u, v)];
}