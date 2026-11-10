#include <iostream>
#include <set>
#include <vector>
using namespace std;

namespace IO {
    static const int BUFF = 1 << 20;
    static char buf[BUFF], *u = buf;
    inline char gc() {
        static char buf[BUFF], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFF, stdin), p1 == p2) ? -1 : *p1++;
    }
    inline void pc(char c) {
        *u++ = c;
        if (u - buf == BUFF)
            fwrite(buf, 1, BUFF, stdout), u = buf;
    }
    inline void flush() {
        fwrite(buf, 1, u - buf, stdout);
        u = buf;
    }
    template <typename T> inline void read(T &x) {
        x = 0;
        char c = gc();
        T f = 1;
        for (; !isdigit(c); c = gc())
            if (c == '-')
                f = -1;
        for (; isdigit(c); c = gc())
            x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    inline void read(char &c, bool graph = 1) {
        c = gc();
        if (graph)
            while (!isgraph(c))
                c = gc();
    }
    inline void read(char *u) {
        char c = gc();
        for (; !isgraph(c); c = gc())
            ;
        for (; isgraph(c); c = gc())
            *u++ = c;
        *u = '\0';
    }
    inline void read(std::string &s) {
        s.clear();
        char c = gc();
        for (; !isgraph(c); c = gc())
            ;
        for (; isgraph(c); c = gc())
            s += c;
    }
    template <typename T, typename... Args> void read(T &x, Args &...args) {
        read(x);
        read(args...);
    }
    template <typename T> inline void write(const T &y) {
        T x = y;
        if (x < 0) {
            pc('-');
            x = -x;
        }
        static char stk[1 << 8], *tp;
        tp = stk;
        do
            *tp++ = (x % 10) ^ 48;
        while (x /= 10);
        while (tp != stk)
            pc(*--tp);
    }


    inline void write(const char &c) { pc(c); }
    inline void write(const std::string &s) {
        for (auto i : s)
            pc(i);
    }
    inline void write(const char *u) {
        for (; *u; ++u)
            pc(*u);
    }
    inline void write(char *u) { write(static_cast<const char *>(u)); }
    template <typename T, typename... Args> void write(const T &x, const Args &...args) {
        write(x);
        write(args...);
    }
    struct __Flusher {
        ~__Flusher() { flush(); }
    } __flusher;
}; // namespace IO
// namespace IO
using IO::read;
using IO::write;
using IO::flush;

#ifdef __clang__
const int N = 2;
#else
const int N = 500010;
#endif

typedef long long ll;
ll n, m, ans;
ll c[N], l[N], r[N], L[N], R[N];
ll st1[N][20], st2[N][20], s[N], t[N];
set<int> S;
vector<int> vec, G[N];
int f(int l, int r){
    if(l > r) return -1e9;
    int t = __lg(r - l + 1);
    return max(st1[l][t], st1[r - (1 << t) + 1][t]);
}
int g(int l, int r){
    if(l > r) return -1e9;
    int t = __lg(r - l + 1);
    return min(st2[l][t], st2[r - (1 << t) + 1][t]);
}
ll get(ll x){
    return 2 * x * (n - x);
}
ll findEdges(int X, vector<int> A, vector<int> B) {
    n = X, m = A.size();
    for (int i = 1; i < n; i ++ )
        L[i] = -1e9, R[i] = 1e9;
    for (int i = 1; i <= m; i ++ ) {
        l[i] = A[i - 1], r[i] = B[i - 1];
        if (l[i] > r[i])
            swap(l[i], r[i]);
        c[l[i]]++, c[r[i]]--;
        L[l[i]] = max(L[l[i]], r[i] - 1), R[r[i] - 1] = min(R[r[i] - 1], l[i]);
    }
    for (int i = 1; i < n; i ++ )
        st1[i][0] = L[i], st2[i][0] = R[i], c[i] += c[i - 1];
    for (int i = 1; i <= 19; i ++ )
        for (int j = 1; j + (1 << i - 1) <= n; j ++ )
            st1[j][i] = max(st1[j][i - 1], st1[j + (1 << i - 1)][i - 1]), st2[j][i] = min(st2[j][i - 1], st2[j + (1 << i - 1)][i - 1]);
    for (int i = 1; i < n; i ++ ) {
        ll x = c[i];
        if (x >= 2)
            continue;
        ans = max(ans, get(i));
        if (!x)
            vec.push_back(i);
    }
    for (int i = 1; i < vec.size(); i ++ ) {
        ll x = vec[i - 1], y = n - vec[i];
        ans = max(ans, 2 * (n * (x + y) - x * x - y * y));
    }
    for (int i = 1; i < n; i ++ ) {
        s[i] = i;
        for (int l = 1, r = i - 1; l <= r; f(((l + r) >> 1) + 1, i) < i
            ? r = (s[i] = ((l + r) >> 1)) - 1 : l = ((l + r) >> 1) + 1) ;
    }
    for (int i = n - 1; i >= 1; i--) {
        t[i] = i;
        for (int l = i + 1, r = n - 1; l <= r; g(i, ((l + r) >> 1) - 1) > i
            ? l = (t[i] = ((l + r) >> 1)) + 1 : r = ((l + r) >> 1) - 1) ;
        G[t[i]].push_back(i);
    }
    for (int i = 1; i <= n; i ++ )
        S.insert(i);
    for (int i = 1; i <= n; i ++ ) {
        for (auto t : G[i - 1])
            S.erase(t);
        if (s[i] > i - 1)
            continue;
        auto it = S.lower_bound(max(s[i], i - n / 2));
        if (it != S.end())
            ans = max(ans, get(i - *it));
        if (it != S.end() && next(it) != S.end())
            ans = max(ans, get(i - *next(it)));
        if (it != S.begin() && *prev(it) >= s[i])
            ans = max(ans, get(i - *prev(it)));
    }
    return ans;
}
