struct Node {
    Node *ch[2];
    int v;
    int s;
    ULL h1, h2;
    bool reverse;

    Node(int v = 0) : v(v) {
        s = 1;
        ch[0] = ch[1] = NULL;
        h1 = h2 = v;
        reverse = false;
    }

    int cmp(int x) {  // x >= 1
        if (ch[0]) {
            if (x <= ch[0]->s) return 0;
            else if (x == ch[0]->s + 1) return -1;
            else return 1;
        } else {
            if (x == 1) return -1;
            else return 1;
        }
    }

    void maintain() {
        s = 1;
        if (ch[0]) s += ch[0]->s;
        if (ch[1]) s += ch[1]->s;

        h1 = 0;
        if (ch[1]) h1 += ch[1]->h1;
        h1 *= HASH;
        h1 += v;
        if (ch[0]) h1 = h1 * pw[ch[0]->s] + ch[0]->h1;

        h2 = 0;
        if (ch[0]) h2 += ch[0]->h2;
        h2 *= HASH;
        h2 += v;
        if (ch[1]) h2 = h2 * pw[ch[1]->s] + ch[1]->h2;
    }

    void pushdown() {
        if (reverse) {
            if (ch[0]) {
                ch[0]->reverse ^= 1;
                swap(ch[0]->ch[0], ch[0]->ch[1]);
                swap(ch[0]->h1, ch[0]->h2);
            }
            if (ch[1]) {
                ch[1]->reverse ^= 1;
                swap(ch[1]->ch[0], ch[1]->ch[1]);
                swap(ch[1]->h1, ch[1]->h2);
            }
            reverse = false;
        }
    }
};

void rotate(Node *&o, int d) {
    Node *k = o->ch[d ^ 1];
    o->ch[d ^ 1] = k->ch[d];
    k->ch[d] = o;
    o->maintain();
    k->maintain();
    o = k;
}

// 1 <= k <= total number
void splay(Node *&o, int k) {
    o->pushdown();
    int d = o->cmp(k);
    if (d == 1) {
        k--;
        if (o->ch[0]) k -= o->ch[0]->s;
    }
    if (d != -1) {
        Node *p = o->ch[d];
        p->pushdown();
        int d2 = p->cmp(k);
        int k2 = k;
        if (d2 == 1) {
            k2--;
            if (p->ch[0]) k2 -= p->ch[0]->s;
        }
        if (d2 != -1) {
            splay(p->ch[d2], k2);
            if (d == d2) rotate(o, d ^ 1); else rotate(o->ch[d], d);
        }
        rotate(o, d ^ 1);
    }
}

// Combine left and right. All left elements are smaller than right elements. Right can be NULL but left cannot.
Node *merge(Node *left, Node *right) {
    splay(left, left->s);
    left->ch[1] = right;
    left->maintain();
    return left;
}

// Put first small k points in left and the other are in right. 1 <= k <= o->s. When k == o->s, right == NULL;
void split(Node *o, int k, Node *&left, Node *&right) {
    splay(o, k);
    left = o;
    if (o->ch[1]) right = o->ch[1]; else right = NULL;
    o->ch[1] = NULL;
    o->maintain();
}