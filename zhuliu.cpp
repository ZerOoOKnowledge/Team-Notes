struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int n, m;
vector<Edge> edges;
int id[N], inw[N], pre[N], pass[N];

// id为缩点后的编号，inw为入边的value，pre为入边的起点，pass用于判断是否在环中
// O(nm)
int ZhuLiu(int root) {
    int ans = 0;
    for (;;) {
        for (int i = 0; i < n; i++) {  // 初始化
            inw[i] = INF;
            pre[i] = pass[i] = id[i] = -1;
        }
        for (int i = 0; i < edges.size(); i++) {  // 选择最小的入边
            Edge &e = edges[i];
            if (e.w < inw[e.v] && e.u != e.v) {
                inw[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        inw[root] = 0;
        pre[root] = root;
        for (int i = 0; i < n; i++) {  // 有点无法到达
            if (inw[i] == INF) return -1;
            ans += inw[i];
        }

        int idx = 0; // 缩点后的编号
        for (int i = 0; i < n; i++) {  // 判断环+缩点
            int t = i;
            while (pass[t] == -1) {
                pass[t] = i;
                t = pre[t];
            }
            if (pass[t] != i || t == root) continue;
            id[t] = idx;
            for (int j = pre[t]; j != t; j = pre[j]) id[j] = idx;
            idx++;
        }
        if (idx == 0) return ans;
        for (int i = 0; i < n; i++)
            if (id[i] == -1) id[i] = idx++;

        // 重新建图
        for (int i = 0; i < edges.size(); i++) {
            Edge &e = edges[i];
            e.w -= inw[e.v];
            e.u = id[e.u];
            e.v = id[e.v];
        }
        root = id[root];
        n = idx;
    }
}