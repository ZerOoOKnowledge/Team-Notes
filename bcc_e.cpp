struct Edge {
    int next;
    Edge(int next): next(next) {}
};

int pre[N], dfs_clock, ebc_cnt, ebcno[N];
bool bridge[2 * M], vis[N];
vector<Edge> edges;
vector<int> G[N], ebc[N];

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    for (int i = 0; i < G[u].size(); i++) {
        int v = edges[G[u][i]].next;
        if (!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv > pre[u]) {
                bridge[G[u][i]] = true;
                bridge[G[u][i] ^ 1] = true;
            }
        } else if (pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return lowu;
}

void dfs2(int u) {
    vis[u] = true;
    ebcno[u] = ebc_cnt;
    ebc[ebc_cnt].push_back(u);
    for (int i = 0; i < G[u].size(); i++) {
        if (bridge[G[u][i]]) continue;
        int v = edges[G[u][i]].next;
        if (vis[v]) continue;
        dfs2(v);
    }
}