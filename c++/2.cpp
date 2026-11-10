#include <stdio.h>
const int maxn = 6005;
int n;
int x[maxn], y[maxn], cnt[4][4];
long long ans;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        cnt[x % 4][y % 4]++;
    }
    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
            for (int c = 0; c < 4; c++)
                for (int d = 0; d < 4; d++)
                    for (int e = 0; e < 4; e++)
                        for (int f = 0; f < 4; f++)
                            if ((gcd(a - c, b - d) + gcd(a - e, b - f) + gcd(c - e, d - f)) % 4 == 0) {
                                int x, y, z;
                                x = cnt[a][b], cnt[a][b]--, y = cnt[c][d], cnt[c][d]--, z = cnt[e][f];
                                ans += 1ll * x * y * z;
                                cnt[a][b]++, cnt[c][d]++;
                            }
    printf("%lld\n", ans / 6ll);
    return 0;
}
