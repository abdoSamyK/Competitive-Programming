// monotonoic stack
// get its idx_s (-1 if no such that)
int n;
vector<int> v;

// get (idx) of previous greater element for each element
vector<int> prv_greater() {
  vector<int> prv_g(n, -1);
  stack<int> st;

  for (int i = 0; i < n; ++i) {

    while (!st.empty() && v[st.top()] <= v[i])
      st.pop();

    if (!st.empty())
      prv_g[i] = st.top();

    st.push(i);
  }
  return prv_g;
}