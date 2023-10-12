#define N_MAX 100005
int parent[N_MAX];
int setSize[N_MAX];
class DSU {
public:
    int n;

    DSU(int n) {
        this->n = n;
        for(int i = 1; i <= n; i++) parent[i] = i,setSize[i] = 1;
    }

    int find_parent(int u) {
        return parent[u] = (parent[u] == u ? u : find_parent(parent[u]));
    }

    void union_sets(int u, int v) {
        u = find_parent(u);
        v = find_parent(v);
        if(u!=v) {
            if(setSize[u]<setSize[v]) swap(u,v);
            parent[v] = u;
            setSize[u] += setSize[v];
        }
    }
};