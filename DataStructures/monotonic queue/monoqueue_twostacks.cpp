struct monoqueue {
  stack<pair<int, int>> in, out;

  int merge(int a, int b) { // find min
    return min(a, b);
  }

  void push(int x) {
    int val = in.empty() ? x : merge(x, in.top().second);
    in.push({x, val});
  }

  void move() {
    if (!out.empty()) return;

    while (!in.empty()) {
      int x = in.top().first;
      in.pop();

      int val = out.empty() ? x : merge(x, out.top().second);
      out.push({x, val});
    }
  }

  void pop() {
    move();
    out.pop();
  }

  int front() {
    move();
    return out.top().first;
  }

  size_t get_size() {
    return (in.size() + out.size());
  }

  int get() {
    if (in.empty()) return out.top().second;
    if (out.empty()) return in.top().second;
    return merge(in.top().second, out.top().second);
  }

  bool empty() {
    return in.empty() && out.empty();
  }
};
