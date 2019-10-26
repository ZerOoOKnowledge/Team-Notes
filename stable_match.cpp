int prefer[N][N], order[N][N], next[N], n;
int husband[N], wife[N];
queue<int> q;

void engage(int man, int woman) {
    int m = husband[woman];
    if (m != -1) q.push(m);
    wife[man] = woman;
    husband[woman] = man;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> prefer[i][j];
                prefer[i][j]--;
            }
            next[i] = 0;
            q.push(i);
        }
        for (int i = 0; i < n; i++) {
            int x;
            for (int j = 0; j < n; j++) {
                cin >> x;
                x--;
                order[i][x] = j;
            }
            husband[i] = -1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int woman = prefer[u][next[u]++];
            if (husband[woman] == -1 || order[woman][u] < order[woman][husband[woman]]) engage(u, woman);
            else q.push(u);
        }
        for (int i = 0; i < n; i++) cout << wife[i] + 1 << '\n';
        if (T) cout << '\n';
    }
    return 0;
}