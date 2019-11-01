int fa[N], ch[N][2], val[N], Xor[N];
bool rev[N];

bool isRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
bool get(int x) { return ch[fa[x]][1] == x; }

inline void maintain(int x) {
    Xor[x] = Xor[ch[x][0]] ^ Xor[ch[x][1]] ^ val[x];
}

inline void pushdown(int x) {
    if (rev[x]) {
        rev[x] = false;
        rev[ch[x][0]] ^= 1;
        swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
        rev[ch[x][1]] ^= 1;
        swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
    }
}

inline void update(int x) {
    if (!isRoot(x)) update(fa[x]);
    pushdown(x);
}

inline void rotate(int x) {
    int y = fa[x], z = fa[y], k = get(x);
    if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
    ch[y][k] = ch[x][k ^ 1], fa[ch[x][k ^ 1]] = y;
    ch[x][k ^ 1] = y, fa[y] = x, fa[x] = z;
    maintain(y), maintain(x);
}

inline void splay(int x) {
    update(x);
    for (int f; (f = fa[x]) && !isRoot(x); rotate(x)) {
        if (!isRoot(f)) rotate(get(f) == get(x) ? f : x);
    }
}

inline int access(int x) {
    int p;
    for (p = 0; x; p = x, x = fa[x]) {
        splay(x);
        ch[x][1] = p;
        maintain(x);
    }
    return p;
}

inline void makeRoot(int x) {
    access(x);
    splay(x);
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
}

inline int findRoot(int x) {  // The root of the whole tree
    access(x); splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    splay(x);  // Ensure time complexity
    return x;
}

inline void split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
}

inline bool link(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x) return false;  // if ensured, delete.
    fa[x] = y;
    return true;
}

inline bool cut(int x, int y) {
    split(x, y);
    if (findRoot(y) != x || fa[y] != x || ch[y][0]) return false;  // if ensured, delete
    fa[y] = ch[x][1] = 0;
    maintain(x);
    return true;
}