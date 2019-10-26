struct GomoryHu {
  int n;
  vector<Dinic::Edge> edges;
  vector<vector<pii>> adj;

  void init(int n) {
    this->n = n;
    adj = vector<vector<pii>>(n);
    edges.clear();
  }

  void addEdge(int from, int to, int cap) {
    edges.eb(from, to, cap, 0);
  }

  void solve() {
    set<int> s;
    REP(i, n) s.emplace(i);
    solve(s);
  }

  void solve(const set<int> &ini) {
    if (ini.size() == 1) return;
    static Dinic solver;
    int source = *ini.begin(), sink = *ini.rbegin();
    solver.init(n);
    for (const auto &e : edges) solver.addEdge(e.from, e.to, e.cap);
    int w = solver.maxflow(source, sink);
    set<int> s, t;
    solver.bfs();
    REP(i, n) if (ini.count(i)) {
      if (solver.vis[i]) s.emplace(i);
      else t.emplace(i);
    }
    solve(s);
    solve(t);
    adj[sink].eb(source, w);
    adj[source].eb(sink, w);
  }
};