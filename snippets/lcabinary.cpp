const int nodemax = 2e5 + 5;
const int l = 21;
int parents[nodemax][l];
int tin[nodemax], tout[nodemax];
int timer = 0;
vector<vector<int>> adj;

void dfs(int u, int par)
{
    tin[u] = ++timer;
    parents[u][0] = par;

    for (auto i : adj[u])
    {
        if (i == par)
            continue;
        dfs(i, u);
    }
    tout[u] = ++timer;
}

bool isAncestor(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v)
{
    if (isAncestor(u, v))
        return u;
    if (isAncestor(v, u))
        return v;

    for (int i = l - 1; i >= 0; i--)
    {
        if (parents[u][i] == -1)
            continue;
        if (!isAncestor(parents[u][i], v))
            u = parents[u][i];
    }
    // cout<<u<<endl;
    return parents[u][0];
}

void preprocess(int n)
{
    dfs(1, -1);
    for (int i = 1; i < l; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            parents[j][i] = ((parents[j][i - 1] == -1) ? -1 : parents[parents[j][i - 1]][i - 1]);
        }
    }
}