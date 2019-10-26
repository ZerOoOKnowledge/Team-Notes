struct Maximum_Clique {
    int n;  // Index starts from 1
    bool G[N][N];
    int p[N][N];  // The vertices included in the complete subgraph
    int maxm[N];  // maxm[i]: The maximum clique can be obtained use vertices index >= i
    int ans;

    void init() {
        memset(G, 0, sizeof(G));
        memset(maxm, 0, sizeof(maxm));
        ans = 0;
    }

    void AddEdge(int i, int j) { G[i][j] = G[j][i] = true; }

    bool dfs(int tot, int np) {
        if (np == 0) {
            if (ans < tot) { ans = tot; return true; }
            else return false;
        }

        for (int i = 0; i < np; i++) {
            if (np - i + tot <= ans) return false;  // Won't get better solution
            int u = p[tot][i];
            if (maxm[u] + tot <= ans) return false;  // Won't get better solution

            int next_np = 0;
            for (int j = i + 1; j < np; j++) {
                int v = p[tot][j];
                if (G[u][v]) p[tot + 1][next_np++] = v;
            }

            if (dfs(tot + 1, next_np)) return true;  // Won't get better solution continue searching
        }
        return false;
    }

    void solve() {
        for (int i = n; i >= 1; i--) {
            int np = 0;
            for (int j = i + 1; j <= n; j++)
                if (G[i][j]) p[1][np++] = j;
            dfs(1, np);
            maxm[i] = ans;
        }
    }
};
