vector<int> out[N];
int pre[N], lowlink[N], sccno[N], dfs_clock, scc_cnt;
stack<int> s;

void dfs(int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    s.push(u);
    for (int i : out[u])
        if (!pre[i]) {
            dfs(i);
            lowlink[u] = min(lowlink[u], lowlink[i]);
        } else if (!sccno[i]) {
            lowlink[u] = min(lowlink[u], pre[i]);
        }
    if (lowlink[u] == pre[u]) {
        scc_cnt++;
        for (;;) {
            int x = s.top(); s.pop();
            sccno[x] = scc_cnt;
            if (x == u) break;
        }
    }
}

void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for (int i = 0; i < n; i++)
        if (!pre[i]) dfs(i);
}
