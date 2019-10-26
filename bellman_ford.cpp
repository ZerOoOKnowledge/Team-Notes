struct BellmanFord {
    int n, m;
    vector<Edge> edges;
    vector<int> G[N];
    bool inq[N];        // 是否在队列中
    int d[N];
    int p[N];           // 上一条边
    int cnt[N];         // 进队次数

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int dist) {
        edges.push_back(Edge(from, to, dist));
        m = edges.size();
        G[from].push_back(m - 1);
    }

    bool bellman_ford(int s) {
        queue<int> Q;
        memset(inq, false, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) d[i] = INF;
        d[s] = 0;
        inq[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for (int i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.dist) {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = G[u][i];
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        Q.push(e.to);
                        if (++cnt[e.to] > n) return false;
                    }
                }
            }
        }
        return true;
    }
};