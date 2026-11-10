#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> a[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> b[i][j];

    // 1. 构建二维初始高度矩阵
    vector<vector<int>> ha(n, vector<int>(m, 0));
    vector<vector<int>> hb(n, vector<int>(m, 0));

    auto build_height = [&](const vector<vector<int>>& grid, vector<vector<int>>& h) {
        h[0][0] = grid[0][0];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 && j == 0) continue;
                if (j > 0) {
                    if (grid[i][j] == (grid[i][j-1] + 1) % 3) h[i][j] = h[i][j-1] + 1;
                    else h[i][j] = h[i][j-1] - 1;
                } else {
                    // 第一列，只能从上方推导
                    if (grid[i][0] == (grid[i-1][0] + 1) % 3) h[i][0] = h[i-1][0] + 1;
                    else h[i][0] = h[i-1][0] - 1;
                }
            }
        }
    };

    build_height(a, ha);
    build_height(b, hb);

    // 2. 匹配奇偶性 (若基准点奇偶性不同，整体偏移3)
    if (abs(ha[0][0] % 2) != abs(hb[0][0] % 2)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) hb[i][j] += 3;
    }

    // 3. 枚举 6k 整体偏移，找到距离和最小的目标高度面
    long long min_cost = -1;
    int best_k = 0;
    // N*M <= 1000, 高度差极限在 1000 量级
    for (int k = -1000; k <= 1000; ++k) {
        long long cur = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cur += abs(ha[i][j] - (hb[i][j] + 6 * k));
            }
        }
        if (min_cost == -1 || cur < min_cost) {
            min_cost = cur;
            best_k = k;
        }
    }

    vector<vector<int>> tar(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) tar[i][j] = hb[i][j] + 6 * best_k;

    // 4. BFS 模拟二维高度面的翻折
    vector<pair<pair<int, int>, int>> ops;
    queue<pair<int, int>> q;
    vector<vector<bool>> st(n, vector<bool>(m, false));

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    auto check_and_push = [&](int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= m || st[r][c]) return;
        
        bool can_up = true, can_down = true;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (ha[nr][nc] <= ha[r][c]) can_up = false; // 周围必须严格比它高才能网上翻
                if (ha[nr][nc] >= ha[r][c]) can_down = false; // 周围必须严格比它低才能往下翻
            }
        }

        if (ha[r][c] < tar[r][c] && can_up) {
            q.push({r, c});
            st[r][c] = true;
        } else if (ha[r][c] > tar[r][c] && can_down) {
            q.push({r, c});
            st[r][c] = true;
        }
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) check_and_push(i, j);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        st[r][c] = false; 

        bool can_up = true, can_down = true;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (ha[nr][nc] <= ha[r][c]) can_up = false;
                if (ha[nr][nc] >= ha[r][c]) can_down = false;
            }
        }

        if (ha[r][c] < tar[r][c] && can_up) {
            ha[r][c] += 2;
            ops.push_back({{r + 1, c + 1}, (ha[r][c] % 3 + 3) % 3});
            check_and_push(r, c);
            for (int i = 0; i < 4; ++i) check_and_push(r + dx[i], c + dy[i]);
        } else if (ha[r][c] > tar[r][c] && can_down) {
            ha[r][c] -= 2;
            ops.push_back({{r + 1, c + 1}, (ha[r][c] % 3 + 3) % 3});
            check_and_push(r, c);
            for (int i = 0; i < 4; ++i) check_and_push(r + dx[i], c + dy[i]);
        }
    }

    cout << ops.size() << "\n";
    for (auto& op : ops) {
        // 输出操作：1 行 列 新颜色
        cout << op.first.first << " " << op.first.second << " " << op.second << "\n";
    }

    return 0;
}
