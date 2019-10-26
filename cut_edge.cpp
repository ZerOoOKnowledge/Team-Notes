// 连通图的割顶和桥
int pre[N], dfs_clock, low[N];  // low[u]: u及其后代能连回的最早祖先的pre值
bool cut[N];  // cut[i]代表i是否为割顶
vector<pair<int, int>> bridge;  // bridge记录所有的桥
vector<int> G[N];

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock, child = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!pre[v]) {  // son
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= pre[u]) cut[u] = true;
            if (lowv > pre[u]) bridge.push_back(pair<int, int>(u, v));
        } else if (pre[v] < pre[u] && v != fa) {  // 反向边
            lowu = min(lowu, pre[v]);
        }
    }
    if (fa < 0 && child == 1) cut[u] = false;
    low[u] = lowu;
    return lowu;
}