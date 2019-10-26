// Get until f[m]. Actually to f[m-1] should be fine (i < m - 1).
void getFail(char* P, int* f) {
    int m = strlen(P);
    f[0] = 0; f[1] = 0;
    for(int i = 1; i < m; i++) {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i + 1] = P[i] == P[j] ? j + 1 : 0;
    }
}

// find P in T. len(P) <= len(T).
void find(char* T, char* P, int* f) {
    getFail(P, f);
    int n = strlen(T), m = strlen(P), j = 0;
    for(int i = 0; i < n; i++) {
        while(j && T[i] != P[j]) j = f[j];
        if(T[i] == P[j]) j++;
        if(j == m) printf("%d\n", i - m + 1);
    }
}
