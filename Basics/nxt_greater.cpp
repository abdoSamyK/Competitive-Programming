// monotonoic stack
// get its idx_s (-1 if no such that)
int n;
vector<int> v;

// get (idx) of next greater element for each element
vector<int> nxt_greater() {
  vector<int> nxt_g(n, -1);
  stack<int> st;

  for (int i = 0; i < n; ++i) {

    while (!st.empty() && v[i] > v[st.top()]) {
      nxt_g[st.top()] = i;
      st.pop();
    }

    st.push(i);
  }
  return nxt_g;
}