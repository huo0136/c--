#include<bits/stdc++.h>
using namespace std;

int build[105][2] = {0};   // build[u][0/1] = u 的左右孩子
int n, x, y;
int minstep = INT_MAX;     // 改成大数

// dir: 进入 root 的方向。0=起点，1=从父亲下来(向下)，2=从孩子上来(向上)
void find(int root, int step, int dir)
{
    if (root == y) {
        minstep = min(minstep, step);
        return;
    }

    // 找 root 的父亲
    int father = -1;
    int which = -1;   // 0 表示 build[father][0]==root，1 表示 [1]
    for (int i = 1; i <= n; i++) {
        if (build[i][0] == root) { father = i; which = 0; break; }
        if (build[i][1] == root) { father = i; which = 1; break; }
    }

    // 向下走孩子（代价 1）
    if (build[root][0] != 0) find(build[root][0], step + 1, 1);
    if (build[root][1] != 0) find(build[root][1], step + 1, 1);

    // 向上走父亲（代价 2），断边防回头
    if (father != -1) {
        build[father][which] = 0;              // 断开 father -> root
        find(father, step + 2, 2);
        build[father][which] = root;           // 恢复
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; i++) {              // n 个点，n-1 条边
        int u, v;
        cin >> u >> v;
        if (build[u][0] == 0) build[u][0] = v;
        else build[u][1] = v;
    }
    cin >> x >> y;
    find(x, 0, 0);
    cout << minstep;
    return 0;
}