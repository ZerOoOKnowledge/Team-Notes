// return the last row with pivot. If no solution, return -1.
int gauss(double a[][N], int n, int m, vector<int> &loc) {
    int row = 0, col = 0;
    loc.assign(n, 0);  // pivot index
    for (row = 0; row < n && col < m; ) {
        int id = -1;
        for (int j = row; j < n; ++j) {
            if (abs(a[j][col]) > eps) {
                id = j;
                break;
            }
        }
        if (id == -1) { ++col; continue; }

        loc[row] = col;
        for (int j = col; j <= m; ++j) swap(a[row][j], a[id][j]);
        for (int j = m; j >= col; --j) a[row][j] /= a[row][col];

        for (int j = row + 1; j < n; ++j) {
            for (int k = m; k >= col; --k) a[j][k] -= a[row][k] * a[j][col];
        }

        ++row; ++col;
    }

    for (int i = row; i < n; ++i) {
        if (abs(a[i][m]) > eps) return -1;
    }

    for (int i = row - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            for (int k = m; k >= loc[i]; --k) a[j][k] -= a[i][k] * a[j][loc[i]];
        }
    }

    return row;
}