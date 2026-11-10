#include <iostream>
#include <unordered_map>
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
const int N = 1000010;
#endif

typedef long long ll;
const int mod = 1e9 + 7;
ll n, m;
ll low[N], dfn[N], stk[N];
int num, tot, etop;
ll ans = 0, pan = 0;
bool check = 0;
pair<ll, ll> pai[N];
vector<ll> linker[N];
vector<ll> nodes;
vector<pair<ll, ll>> paii;
unordered_map<ll, ll> deg;
unordered_map<ll, vector<ll>> adj;
vector<ll> lens;
void checkk(){
    ll sz = nodes.size();
    if(sz < 3) return ;
    deg.clear();
    for (auto &e : paii){
        deg[e.first] ++ ;
        deg[e.second] ++ ;
    }
    ll sd2 = 0;
    ll hub1 = -1, hub2 = -1;
    for (auto &p : deg) {
        ll d = p.second;
        if (d > 2) {
            sd2 ++ ;
            if (sd2 == 1)
                hub1 = p.first;
            else if (sd2 == 2)
                hub2 = p.first;
        } else if (d != 2) {
            puts("NIE");
            exit(0);
        }
    }
    if (sd2 == 0) {
        ll L = sz;
        if ((ll)nodes.size() != sz) {
            puts("NIE");
            exit(0);
        }
        if (!check) {
            check = true;
            pan = L;
        } else if (pan != L) {
            puts("NIE");
            exit(0);
        }
        ans = (ans + 2LL * L) % mod; 
    }else if (sd2 == 2) {
        ll k = deg[hub1];
        if (deg[hub2] != k) {
            puts("NIE");
            exit(0);
        }
        adj.clear();
        for (auto &e : paii) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }
        lens.clear();
        for (ll nxt : adj[hub1]) {
            ll cur = nxt, prev = hub1;
            ll len = 1;
            while (cur != hub2) {
                ll ne = -1;
                for (ll nb : adj[cur])
                    if (nb != prev) {
                        ne = nb;
                        break;
                    }
                if (ne == -1) {
                    puts("NIE");
                    exit(0);
                }
                prev = cur;
                cur = ne;
                len ++ ;
            }
            lens.push_back(len);
        }
        for (ll l : lens)
            if (l != lens[0]) {
                puts("NIE");
                exit(0);
            }

        ll len = lens[0];
        ll L = 2 * len; 
        ll cyc = (ll)k * (k - 1) % mod;
        cyc = cyc * L % mod; 
        if (!check) {
            check = true;
            pan = L;
        } else if (pan != L) {
            puts("NIE");
            exit(0);
        }
        ans = (ans + cyc) % mod;
    } else {
        puts("NIE");
        exit(0);
    }
}
void tarjan(ll u, ll fa){
    low[u] = dfn[u] = ++ tot;
    stk[ ++ num] = u;
    for (auto v : linker[u]) {
        if (v == fa)
            continue;
        if (!dfn[v]) {
            pai[++etop] = {u, v};
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) { 
                nodes.clear();
                paii.clear();
                nodes.push_back(u);
                ll y;
                do{
                    y = stk[num--];
                    nodes.push_back(y);
                } while (y != v);
                pair<ll, ll> e;
                do {
                    e = pai[etop -- ];
                    paii.push_back(e);
                } while (!(e.first == u && e.second == v));
                checkk();
            }
        } else {
            if (dfn[v] < dfn[u])
                pai[ ++ etop] = {u, v};
            low[u] = min(low[u], dfn[v]);
        }
    }
}
signed main(){
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; i ++ ){
        cin >> a >> b;
        linker[a].push_back(b);
        linker[b].push_back(a);
    }
    for (int i = 1; i <= n; i ++ ){
        if(!dfn[i]){
            num = etop = 0;
            tarjan(i, 0);
            if (num > 0) {
                nodes.clear();
                paii.clear();
                for (ll j = 1; j <= num; j ++ )
                    nodes.push_back(stk[j]);
                for (ll j = 1; j <= etop; j ++ )
                    paii.push_back(pai[j]);
                checkk();
                num = 0;
                etop = 0;
            }
        }
    }
    if(!check) puts("BRAK");
    else{
        puts("TAK");
        cout << pan << ' ' << ans;
    }
    return 0;
}
