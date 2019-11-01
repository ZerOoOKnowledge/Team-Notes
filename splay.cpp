int tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];
void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
bool get(int x) { return x == ch[fa[x]][1]; }  // left son: 0 or right son: 1
void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0; }

void rotate(int x) {
    int y = fa[x], z = fa[y], chk = get(x);
    ch[y][chk] = ch[x][chk ^ 1];
    fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z) ch[z][y == ch[z][1]] = x;
    maintain(y);
    maintain(x);
}

void splay(int &root, int x) {  // Splay node x to the root
    for (int f; (f = fa[x]); rotate(x)) {
        if (fa[f]) rotate(get(x) == get(f) ? f : x);
    }
    root = x;
}

void insert(int &root, int x) {
    if (!root) {
        val[++tot] = x;
        cnt[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        fa[tot] = 0;
        root = tot;
        maintain(root);
        return;
    }

    int cur = root, f = 0;
    for (;;) {
        if (val[cur] == x) {
            ++cnt[cur];
            maintain(cur);
            splay(root, cur);
            break;
        }
        f = cur;
        cur = ch[cur][val[cur] < x];
        if (!cur) {
            val[++tot] = x;
            cnt[tot] = 1;
            fa[tot] = f;
            ch[f][val[f] < x] = tot;
            ch[tot][0] = ch[tot][1] = 0;
            maintain(tot);
            splay(root, tot);
            break;
        }
    }
}

int rk(int &root, int x) {  // get the rank of x; if x exists, splay x to the root
    int ans = 0, cur = root;
    for (;;) {
        if (cur == 0) return ans + 1;
        if (x < val[cur]) cur = ch[cur][0];
        else {
            ans += sz[ch[cur][0]];
            if (x == val[cur]) {
                splay(root, cur);
                return ans + 1;
            }
            ans += cnt[cur];
            cur = ch[cur][1];
        }
    }
}

int kth(int &root, int k) {  // need k <= size
    int cur = root;
    for (;;) {
        if (ch[cur][0] && k <= sz[ch[cur][0]]) cur = ch[cur][0];
        else {
            k -= cnt[cur] + sz[ch[cur][0]];
            if (k <= 0) return val[cur];
            cur = ch[cur][1];
        }
    }
}

// The node with the number smaller than root (if doesn't exists return 0)
int pre(int root) {
    int cur = ch[root][0];
    while (ch[cur][1]) cur = ch[cur][1];
    return cur;
}

// The node with the number larger than root (if doesn't exists return 0)
int nxt(int root) {
    int cur = ch[root][1];
    while (ch[cur][0]) cur = ch[cur][0];
    return cur;
}

void erase(int &root, int x) {
    rk(root, x);  // splay x to root
    if (cnt[root] > 1) {
        --cnt[root];
        maintain(root);
        return;
    }
    if (!ch[root][0]) {
        int cur = root;
        root = ch[root][1];
        fa[root] = 0;
        clear(cur);
        return;
    }
    if (!ch[root][1]) {
        int cur = root;
        root = ch[root][0];
        fa[root] = 0;
        clear(cur);
        return;
    }
    int p = pre(root), cur = root;
    splay(root, p);
    fa[ch[cur][1]] = p;
    ch[p][1] = ch[cur][1];
    clear(cur);
    maintain(root);
}

void pushdown(int o) {  // remember to update the data in sons
    
}

void splay_sz(int &root, int k) {
    int cur = root;
    for (;;) {
        pushdown(cur);
        if (sz[ch[cur][0]] >= k) cur = ch[cur][0];
        else {
            k -= sz[ch[cur][0]] + cnt[cur];
            if (k <= 0) { splay(root, cur); return; }
            cur = ch[cur][1];
        }
    }
}

// left with size k: 1 <= k <= sz[root]
void split(int root, int k, int &left, int &right) {
    splay_sz(root, k);
    left = root;
    right = ch[left][1];
    ch[left][1] = 0;
    fa[right] = 0;
    maintain(left);
}

int merge(int left, int right) {
    if (left == 0) return right;
    if (right == 0) return left;
    splay_sz(left, sz[left]);
    ch[left][1] = right;
    fa[right] = left;
    maintain(left);
    return left;
}