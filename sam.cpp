struct State {
    int len, link;
    map<char, int> next;
} st[MAXLEN * 2];

int sz, last;
int cnt[MAXLEN * 2];

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].next.clear();
    sz = 1;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    cnt[cur] = 1;
    st[cur].next.clear();
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}