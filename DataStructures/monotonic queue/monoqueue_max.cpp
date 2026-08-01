// find max element in each sliding window
struct monoqueue_max {
  deque<int> dq;

  void push(int x) {
    while (!dq.empty() && dq.back() < x) {
      dq.pop_back();
    }
    dq.push_back(x);
  }

  void pop(int x) {
    if (!dq.empty() && dq.front() == x)
      dq.pop_front();
  }

  int getMax() {
    return dq.front();
  }

  bool empty() {
    return dq.empty();
  }
};