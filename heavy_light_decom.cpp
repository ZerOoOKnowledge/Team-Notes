int dep[N], fa[N], sz[N], top[N], pos[N], son[N], tot;
vector<int> G[N];

int dfs(int u, int pa, int depth) {
    dep[u] = depth;
    fa[u] = pa;
    sz[u] = 1;

    for (int v : G[u])
        if (v != fa[u]) {
            sz[u] += dfs(v, u, depth + 1);
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    return sz[u];
}

void dfs2(int u, int tp) {
    top[u] = tp;
    pos[u] = ++tot;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

void query(int x, int y) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(x, y);
            swap(tx, ty);
        }

        query(1, 1, n, pos[tx], pos[x]);
        x = fa[tx];
    }
}