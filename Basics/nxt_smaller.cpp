// monotonoic stack
// get its idx_s (-1 if no such that)
int n;
vector<int> v;

// get (idx) of next smaller element for each element
vector<int> nxt_smaller() {
  vector<int> nxt_s(n, -1);
  stack<int> st;

  for (int i = 0; i < n; ++i) {

    while (!st.empty() && v[i] < v[st.top()]) {
      nxt_s[st.top()] = i;
      st.pop();
    }

    st.push(i);
  }
  return nxt_s;
}
