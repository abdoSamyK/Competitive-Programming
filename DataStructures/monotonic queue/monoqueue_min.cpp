// find min element in each sliding window
struct monoqueue_min {
  deque<int> dq;

  void push(int x) {
    while (!dq.empty() && dq.back() > x) {
      dq.pop_back();
    }
    dq.push_back(x);
  }

  void pop(int x) {
    if (!dq.empty() && dq.front() == x)
      dq.pop_front();
  }

  int getMin() {
    return dq.front();
  }

  bool empty() {
    return dq.empty();
  }
};