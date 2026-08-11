/**
*  Case Processing (Light/Heavy SQRT decomposition) =====
*  * problem:
*  given an (n * m) grid, for each distinct number (k),
* find the minimum Manhattan distance between any two appearances of that number.
*: (n * m) <= 2e5, a[i][j] <= (n * m)
*--------------------------------------------------------------------------------
* sol :
*  split the processing into two cases based on a threshold: sq = sqrt(n * m).
*
* -> case 1 (light Numbers): Frequency <= sqrt(n * m)
*  brute force all pairs of coordinates to find the minimum.
*  O(freq^2) per number. *  since the max frequency here is sqrt(NM), the worst-case *  time per light number is (sqrt(NM))^2 = O(NM).
*
* -> Case 2 (Heavy Numbers): Frequency > sqrt(n * m)
*  Multi-source BFS with origin tracking to find collisions.
*  O(N * M) per heavy number.
*  BFS processes the grid in linear time. Because a number must *  appear > sqrt(NM) times to be heavy, there can be at most *  sqrt(NM) heavy numbers in the entire grid.
*
*: O(N * M * sqrt(N * M))
* ============================================================================
*/

//        L   R   U   D
int di[] = {0, 0, -1, 1};
int dj[] = {-1, 1, 0, 0};

void solve() { //
  int n , m;cin >> n >> m;
  int sq = sqrt(n*m);
  vector<vector<int>> g(n, vector<int>(m));
  vector<vector<pair<int, int>>> dis(n, vector<pair<int, int>> (m, {-1, -1})); //{where that path come from, dis}
  vector<vector<int>> cell(n , vector<int>(m));
  vector<vector<pair<int, int>>> fre(n * m + 1); // frequency for each number
  for (int i = 0; i < n; i++) {
    for (int j = 0;j < m; j++) {
      cin >> g[i][j];
      fre[g[i][j]].emplace_back(i, j);
    }
  }

  for (int k = 1;k <= n * m;++k) { // O(n*m * (sqrt(n*m))
    if (fre[k].size() <= 1) {
      cout << -1 << '\n'; // that number does not exist,
    } else if (fre[k].size() <= sq) {
      int ans = 1e9;
      for (int i = 0;i < fre[k].size();++i) {
        for (int j = i + 1;j < fre[k].size();++j) {
          ans = min(ans, (abs(fre[k][i].first - fre[k][j].first) + abs(fre[k][i].second - fre[k][j].second)));
        }
      }
      cout << ans << '\n';
    } else if (fre[k].size() > sq) {
      queue<pair<int, int>> q;
      int cnt = 0;
      for (int i = 0;i < fre[k].size();++i) {
        auto[x, y] = fre[k][i];
        q.emplace(x, y);
        dis[x][y].first = cnt++;
        dis[x][y].second = 0;
        cell[x][y] = k;
      }
      auto valid = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
      };
      int ans = 1e9;
      while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop();
        if (dis[x][y].second >= ans) continue;
        for (int o = 0; o < 4; ++o) {
          int nx = x + di[o], ny = y + dj[o];
          if (valid(nx, ny)) {
            if (cell[nx][ny] == k && dis[nx][ny].first != dis[x][y].first) {
              ans = min(ans, dis[nx][ny].second + dis[x][y].second + 1);
            }
            else if (cell[nx][ny] != k) {
              dis[nx][ny].first = dis[x][y].first;
              dis[nx][ny].second = dis[x][y].second + 1;
              q.emplace(nx, ny);
              cell[nx][ny] = k;
            }
          }
        }
      }
      cout << ans << '\n';
    }
  }
}