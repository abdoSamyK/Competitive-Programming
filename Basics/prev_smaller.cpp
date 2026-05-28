// monotonoic stack
// get its idx_s (-1 if no such that)
int n;
vector<int> v;

// get (idx) of previous smaller element for each element
vector<int> prv_smaller() {
  vector<int> prv_s(n, -1);
  stack<int> st;

  for (int i = 0; i < n; ++i) {

    while (!st.empty() && v[st.top()] >= v[i])
      st.pop();

    if (!st.empty())
      prv_s[i] = st.top();

    st.push(i);
  }
  return prv_s;
}
