int mate[N], link[N], vis[N], fa[N], ss[N];  // mate[i]: matched partner
vector<int> G[N];
int n, ans, tim;

void addEdge(int x, int y) {
    G[x].pb(y);
    G[y].pb(x);
    if (!mate[x] && !mate[y]) {
        mate[mate[x] = y] = x;
        ++ans;
    }
}

int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }

int LCA(int x, int y) {
    ++tim;
    while (ss[x] != tim) {
        if (x) { ss[x]= tim; x = find(link[mate[x]]); }
        swap(x, y);
    }
    return x;
}

void flower(int x, int y, int p, queue<int>& q) {
    while (find(x) != p) {
        link[x] = y;
        fa[y = mate[x]] = fa[x] = p;
        if (vis[y] == 1) { vis[y] = 2; q.push(y); }
        x = link[y];
    }
}

bool match(int x) {
    for (int i = 1; i <= n; ++i) vis[fa[i] = i] = 0;
    vis[x] = 2;
    queue<int> q;
    q.push(x);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : G[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                link[v] = u;
                if (!mate[v]) {
                    while (v) {
                        int cur = mate[link[v]];
                        mate[mate[v] = link[v]] = v;
                        v = cur;
                    }
                    return true;
                } else {
                    vis[mate[v]] = 2;
                    q.push(mate[v]);
                }
            } else if (vis[v] == 2 && find(v) != find(u)) {
                int p = LCA(u, v);
                flower(u, v, p, q);
                flower(v, u, p, q);
            }
        }
    }
    return false;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        if (!mate[i] && match(i)) ++ans;
    }
}