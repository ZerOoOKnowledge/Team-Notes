// Index starts with 0
vector<int> par, dsu_2ecc, dsu_cc, cc_sz, vis;
int bridges, tim;

void init(int n) {
    par.resize(n);
    dsu_2ecc.resize(n);
    dsu_cc.resize(n);
    cc_sz.resize(n);
    vis.resize(n);
    tim = bridges = 0;
    for (int i = 0; i < n; ++i) {
        dsu_2ecc[i] = i;
        dsu_cc[i] = i;
        cc_sz[i] = 1;
        par[i] = -1;
        vis[i] = 0;
    }
}

int find_2ecc(int x) {
    if (x == -1) return x;
    return dsu_2ecc[x] == x ? x : dsu_2ecc[x] = find_2ecc(dsu_2ecc[x]);
}

int find_cc(int x) {
    x = find_2ecc(x);
    return dsu_cc[x] == x ? x : dsu_cc[x] = find_cc(dsu_cc[x]);
}

void make_root(int x) {
    x = find_2ecc(x);
    int root = x;
    int child = -1;
    while (x != -1) {
        int p = find_2ecc(par[x]);
        par[x] = child;
        dsu_cc[x] = root;
        child = x;
        x = p;
    }
    cc_sz[root] = cc_sz[child];
}

void merge_path(int a, int b) {
    ++tim;
    vector<int> path_a, path_b;
    int lca = -1;

    while (lca == -1) {
        if (a != -1) {
            a = find_2ecc(a);
            path_a.pb(a);
            if (vis[a] == tim) lca = a;
            vis[a] = tim;
            a = par[a];
        }
        if (b != -1) {
            b = find_2ecc(b);
            path_b.pb(b);
            if (vis[b] == tim) lca = b;
            vis[b] = tim;
            b = par[b];
        }
    }

    for (int x : path_a) {
        dsu_2ecc[x] = lca;
        if (x == lca) break;
        --bridges;
    }
    for (int x : path_b) {
        dsu_2ecc[x] = lca;
        if (x == lca) break;
        --bridges;
    }
}

void add_edge(int a, int b) {
    a = find_2ecc(a);
    b = find_2ecc(b);
    if (a == b) return;

    int ca = find_cc(a);
    int cb = find_cc(b);

    if (ca != cb) {
        ++bridges;
        if (cc_sz[ca] > cc_sz[cb]) {
            swap(a, b);
            swap(ca, cb);
        }
        make_root(a);
        par[a] = dsu_cc[a] = b;
        cc_sz[cb] += cc_sz[a];
    } else {
        merge_path(a, b);
    }
}