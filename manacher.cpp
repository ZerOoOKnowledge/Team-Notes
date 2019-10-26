struct Manacher {
    string s;
    string s_new;  // The string after modifying
    int p[N * 2];
    // p[i]: the palindrome radius with center at i. The length of max-palindrome centered at i is then p[i] - 1

    void init() {
        s_new.clear();
        for (int i = 0; i < s.length(); i++) {
            s_new.push_back('#');
            s_new.push_back(s[i]);
        }
        s_new.push_back('#');
    }

    int solve() {
        int len = s_new.length();
        int max_len = -1;  // Length of the longest sub-palindrome
        int mx = 0;  // The rightmost point covered by a sub-palindrome (mx itself is not covered)
        int id = 0;  // The center of the rightmost palindrome

        for (int i = 0; i < len; i++) {
            if (i < mx) p[i] = min(p[id * 2 - i], mx - i);
            else p[i] = 1;

            while (i - p[i] >= 0 && i + p[i] < len && s_new[i - p[i]] == s_new[i + p[i]]) p[i]++;

            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }

            max_len = max(max_len, p[i] - 1);
        }
        return max_len;
    }
};
