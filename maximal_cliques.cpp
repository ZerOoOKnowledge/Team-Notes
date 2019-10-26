struct Bron_Kerbosch {
    // Index starts from 1
    int n;
    bool G[N][N];  // The graph
    int R[N][N];  // The vertices currently in the complete graph
    int P[N][N];  // The available vertices that haven't been selected
    int X[N][N];  // The available vertices that have been selected
    int ans;  // The number of maximal cliques

    void init() { memset(G, 0, sizeof(G)); ans = 0; }

    void AddEdge(int i, int j) {
        G[i][j] = G[j][i] = true;
    }

    bool dfs(int tot, int nr, int np, int nx) {
        if (!np) {
            if (!nx) ans++;  // Find a maximal clique
            return ans > 1000;  // Exceed the criteria
        }

        // Find a vertex with the largest degree in P
        int u = -1, maxm = -1;
        for (int i = 1; i <= np; i++) {
            int v = P[tot][i];
            int cnt = 0;
            for (int j = 1; j <= np; j++)
                if (G[P[tot][j]][v]) cnt++;
            if (cnt > maxm) { maxm = cnt; u = v; }
        }

        // All maximal cliques can be divided into two situations: include u or not include u
        // For the first case, we select u first
        // For second case, we must select a vertex v in P \ N(u) and we can select now
        for (int i = 1; i <= np; i++) {
            int v = P[tot][i];
            if (G[u][v]) continue;  // If v is in N(u) (the neighbor of u, u is not included)
            for (int j = 1; j <= nr; j++) R[tot + 1][j] = R[tot][j];
            R[tot + 1][nr + 1] = v;  // Add v to R
            int next_p = 0;
            // Update the P set
            for (int j = 1; j <= np; j++)
                if (P[tot][j] > -1 && G[P[tot][j]][v]) P[tot + 1][++next_p] = P[tot][j];
            int next_x = 0;
            // Update the X set
            for (int j = 1; j <= nx; j++)
                if (G[X[tot][j]][v]) X[tot + 1][++next_x] = X[tot][j];
            if (dfs(tot + 1, nr + 1, next_p, next_x)) return true;

            // Delete v from P and add v to X
            P[tot][i] = -1;
            X[tot][++nx] = v;
        }
        return false;
    }

    void solve() {
        for (int i = 1; i <= n; i++) P[1][i] = i;
        dfs(1, 0, n, 0);
    }
};