
/** Batch Processing (Square Root Rebuilding)
*
*   given an (n × m) grid with initially one black cell.
*   each query:
*     1) Find the minimum distance from a given white cell to any black cell.
*     2) Paint that cell black.
*
*    n*m <= 2e5, q <= 1e5 .
* ------------------------------------------------------------
* idea:
*
* maintain a list of "newly added" black cells.
*
* 1) While the list size <= sqrt(number_of_cells):
*      - Answer each query by brute-force over only these
*        newly added black cells.
*
* 2) Once the list reaches sqrt(number_of_cells):
*      - Run a multi-source BFS/DFS from ALL black cells.
*      - Precompute the minimum distance for every cell.
*      - Clear the temporary list of newly added black cells.
*
* 3) Repeat:
*      - Brute force over newly added black cells.
*       - use the mini between the dis in the array and the bfs result
*      - Rebuild (Step 2) every sqrt(number_of_cells) updates.
*
*   rebuild cost: O(n * m)
*   Rebuild every sqrt(n * m) updates
*   Query cost: O(sqrt(n * m))
*/

//      L   R   U   D
int di[] = {0, 0, -1, 1};
int dj[] = {-1, 1, 0, 0};
void solve() { //
  int n , m;cin >> n >> m;
  int sq = sqrt(n*m);
  int xini, yini;cin >> xini >> yini;
  vector<pair<int, int>> fs;
  fs.emplace_back(xini, yini);

  vector<vector<int>> dis(n + 1, vector<int>(m + 1, 1e9));

  int qu;cin >> qu;
  for (int i = 1;i <= qu;++i) {
    int x, y;cin >> x >> y;
    if (fs.size() == sq) {
      queue<pair<int, int>> q;
      for (auto [nx, ny] : fs) {
        q.emplace(nx, ny);
        dis[nx][ny] = 0;
      }
      fs.clear();

      auto valid = [&](int xx, int yy) {
        return (xx > 0 && xx <= n && yy > 0 && yy <= m);
      };
      while (!q.empty()) {
        auto [nx, ny] = q.front();
        q.pop();

        for (int o = 0;o < 4; ++o) {
          int nnx = nx + di[o], nny = ny + dj[o];
          if (valid(nnx, nny)) {
            if (dis[nnx][nny] > dis[nx][ny] + 1) {
              dis[nnx][nny] = dis[nx][ny] + 1;
              q.emplace(nnx, nny);
            }
          }
        }
      }
      fs.emplace_back(x, y);
      cout << dis[x][y] << '\n';


    } else {
      int mn = dis[x][y];
      for (auto [nx, ny] : fs) {
        mn = min(mn, abs(nx - x) + abs(ny - y));
	   }
      fs.emplace_back(x, y);
      cout << mn << '\n';
    }
  }
}
