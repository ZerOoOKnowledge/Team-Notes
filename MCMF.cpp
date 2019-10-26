struct MCMF {
    int n, m;
    vector<Edge> edges;
    vector<int> G[N];
    //bool inq[N];
    int d[N];
    int h[N];            // 势函数，若原图cost有负数则需做一次Bellman_Ford另h[i] = dist[i]
    int p[N];
    int a[N];            // 可改进量

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool Dijkstra(int s, int t, int &flow, LL &cost) {
        fill(d, d + n, INF);
        d[s] = 0;
        a[s] = INF;

        priority_queue<Node> pq;
        pq.push({ s, 0 });

        while (!pq.empty()) {
            Node u = pq.top(); pq.pop();
            if (u.d > d[u.u]) continue;

            for (int it : G[u.u]) {
                Edge &e = edges[it];
                if (e.cap > e.flow && d[e.to] > d[u.u] + e.cost + h[u.u] - h[e.to]) {
                    d[e.to] = d[u.u] + e.cost + h[u.u] - h[e.to];
                    p[e.to] = it;
                    a[e.to] = min(a[u.u], e.cap - e.flow);
                    pq.push({ e.to, d[e.to] });
                }
            }
        }

        if (d[t] == INF) return false;
        flow += a[t];
        cost += (LL) (d[t] - h[s] + h[t]) * (LL) a[t];
        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        for (int i = 0; i < n; ++i) h[i] += d[i];
        return true;
    }

    int MincostMaxflow(int s, int t, LL &cost) {
        fill(h, h + n, 0);  // Run SPFA to get h if negative edges exist
        int flow = 0;
        cost = 0;
        while (Dijkstra(s, t, flow, cost));
        return flow;
    }
};