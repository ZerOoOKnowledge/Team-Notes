struct Trie {
    int ch[max_node][sigma_size], val[max_node], sz;
    
    void init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }

    int idx(char c) { return c - 'a'; }

    void insert(char *s, int v) {  // Assume v != 0.
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    int query(char *s) {  // If fail, just return 0.
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return val[u];
    }

    // Next part is AC algorithm
    // f[j] means j has already matched
    int f[max_node], last[max_node];

    void getfail() {
        queue<int> q;
        f[0] = 0;
        for (int c = 0; c < sigma_size; c++) {
            int u = ch[0][c];
            if (u) {
                f[u] = 0;
                q.push(u);
                last[u] = 0;
            }
        }

        while (!q.empty()) {
            int r = q.front();
            q.pop();
            for (int c = 0; c < sigma_size; c++) {
                int u = ch[r][c];
                if (!u) continue;  // M2: if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
                q.push(u);
                int v = f[r];
                while (v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

    void print(int j) {
        if (j) {
            printf("%d %d\n", j, val[j]);
            print(last[j]);
        }
    }

    void find(char *s) {
        int n = strlen(s), j = 0;
        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            while (j && !ch[j][c]) j = f[j];  // M2: detele this statement.
            j = ch[j][c];
            if (val[j]) print(j);
            else if (last[j]) print(last[j]);
        }
    }
};