// O(n^3)
struct KM {            // 点从1开始，left[v] == 0代表没有匹配
    int n;             // 每边的个数 (In total 2n)
    int W[N][N];       // 权值
    int Lx[N], Ly[N];  // 顶标
    int left[N];       // 右边第i个点的匹配点
    bool S[N], T[N];   // 左/右是否已经标记(是否在交替路中)，每次找一条交替路
    int slack[N];      // v在!T中，u在S中。slack[v]记录Lx[u] + Ly[v] - W[u][v]的最小值

    void init(int n) {
        this->n = n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) W[i][j] = -INF;
    }

    void AddEdge(int u, int v, int w) {
        W[u][v] = max(W[u][v], w);
    }

    bool match(int u) {
        S[u] = true;
        for(int i = 1; i <= n; i++) if (!T[i]) {
                if (Lx[u] + Ly[i] == W[u][i]) {
                    T[i] = true;
                    if (!left[i] || match(left[i])) {
                        left[i] = u;
                        return true;
                    }
                } else {
                    slack[i] = min(slack[i], Lx[u] + Ly[i] - W[u][i]);
                }
            }
        return false;
    }

    void update() {
        int a = INF;
        for (int i = 1; i <= n; i++) if (!T[i])
                a = min(a, slack[i]);
        for (int i = 1; i <= n; i++) {
            if (S[i]) Lx[i] -= a;
            if (T[i]) Ly[i] += a;
        }
    }

    int solve() {  //存在完美匹配返回值，否则返回-1
        for (int i = 1; i <= n; i++) {
            left[i] = Lx[i] = Ly[i] = 0;
            for (int j = 1; j <= n; j++)
                Lx[i] = max(Lx[i], W[i][j]);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) slack[j] = INF;
            for (;;) {
                for (int j = 1; j <= n; j++) S[j] = T[j] = false;
                if (match(i)) break; else update();
            }
        }

        for (int i = 1; i <= n; i++)
            if (!left[i] || W[left[i]][i] == -INF) return -1;
        int ans = 0;
        for (int i = 1; i <= n; i++) ans += Lx[i] + Ly[i];
        return ans;
    }
};
