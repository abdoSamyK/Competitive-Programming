// two queries
//    1) modify v[i] to x
//    2) get how many elements from [l, r] <= x
// N up to 1e5, q up to 1e4,,,
const int sq =1000;  // or ceil(sqrt(N))
// build: O(n log(sq))

// modify:
// lower_bound + shifting inside one bucket
// O(log(sq) + sq)

// get:
// scan two partial buckets + binary search in each full bucket
// O(sq + (n/sq) * log(sq))

// choose sq according to the constraints.
// larger sq → fewer buckets,
// smaller sq → more buckets,
// Balance these (O(sq + (n/sq) * log(sq))) for the best performance.
// here form sq = [900 -> 1000] give the best,,

void sqrt_decomp() {
  int n, q;cin >> n >> q;
  vector<int> v(n);
  vector<vector<int>> bt((n/sq) + 2);

  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    bt[i/sq].push_back(v[i]);
  }
  for (int i = 0; i <= n/sq; ++i) {
    sort(bt[i].begin(), bt[i].end());
  }


  while (q--) {
    char ch;cin >> ch;
    if (ch == 'M') { // modify v[idx] to x.
      int idx, x;cin >> idx >> x;
      --idx;
      int bkt = idx/sq;
      int old = (int)(lower_bound(bt[bkt].begin(), bt[bkt].end(), v[idx]) - bt[bkt].begin());
      bt[bkt][old] = x;
      if (x < v[idx]) {
        while (old > 0 && bt[bkt][(old - 1)] > x) {
          swap(bt[bkt][(old - 1)], bt[bkt][old]);
          --old;
        }
      } else if (x > v[idx]) {
        while (old + 1 < bt[bkt].size() && x > bt[bkt][(old + 1)]) {
          swap(bt[bkt][(old + 1)], bt[bkt][old]);
          ++old;
        }
      }
      v[idx] = x;
    } else { // get how many elements from [l, r] <= x
      int l, r, x;cin >>l >> r >> x;
      --l, --r;
      ll ans = 0;
      int cl = l/sq; // left cell
      int cr = r/sq; // right cell
      if (cl == cr) { // in the same cell
        for (int i = l;i <= r;++i) {
          if (v[i] <= x) ans++;
        }
      } else {
        // left block before complete buckets
        for (int i = l;i < (cl + 1) * sq;++i) {
          if (v[i] <= x) ans++;
        }
        // complete(middle) buckets
        for (int i = cl + 1; i < cr; ++i) {
          ans += (int)(upper_bound(bt[i].begin(), bt[i].end(), x) - bt[i].begin());
        }
        // right block after complete buckets
        for (int i = (cr * sq);i <= r;++i) {
          if (v[i] <= x) ans++;
        }
      }
      cout << ans << '\n';
    }
  }
}