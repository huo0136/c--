#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n = 10, k = 5, sx = 5, sy = 5;
    int dx[8] = {-2,-1,1,2,2,1,-1,-2};
    int dy[8] = {1,2,2,1,-1,-2,-2,-1};
    vector<vector<bool>> vis(n+1, vector<bool>(n+1, false));
    queue<pair<pair<int,int>,int>> q;
    q.push({{sx,sy},0});
    vis[sx][sy] = true;
    int ans = 0;
    while (!q.empty()) {
        auto [pos, step] = q.front(); q.pop();
        int x = pos.first, y = pos.second;
        ans++;
        if (step == k) continue;
        for (int d = 0; d < 8; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({{nx,ny}, step+1});
            }
        }
    }
    cout << ans << endl;
    return 0;
}