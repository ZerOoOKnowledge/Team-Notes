int n, m, lmatch[N], rmatch[N], d[N];
vector<int> G[N];  // left to right

bool bfs() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (lmatch[i] == 0) { d[i] = 0; q.push(i); }
        else d[i] = INF;
    }
    d[0] = INF;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (d[u] >= d[0]) continue;
        for (int v : G[u]) {
            if (d[rmatch[v]] == INF) {
                d[rmatch[v]] = d[u] + 1;
                q.push(rmatch[v]);
            }
        }
    }
    return d[0] < INF;
}

bool dfs(int u) {
    if (u == 0) return true;

    for (int v : G[u]) {
        if (d[rmatch[v]] == d[u] + 1 && dfs(rmatch[v])) {
            lmatch[u] = v;
            rmatch[v] = u;
            return true;
        }
    }
    return false;
}

int max_match() {  // left size, right size
    fill(lmatch + 1, lmatch + n + 1, 0);
    fill(rmatch + 1, rmatch + m + 1, 0);

    int ans = 0;

    while (bfs()) {
        for (int i = 1; i <= n; ++i) {
            if (lmatch[i] == 0 && dfs(i)) ++ans;
        }
    }
    return ans;
}