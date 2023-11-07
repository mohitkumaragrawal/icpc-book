#include <bits/stdc++.h>
using namespace std;
// pi[i] = longest proper prefix of s[0..i] which is alos a suffix;
// online algorithm;
vector<int> prefix_function(string const& s) {
  int n = s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
}
// Applications:
// finding occurences: Concat 's # t' and check in where pi[i] = |S|
// counting prefixes;
vector<int> prefix_occurences(vector<int> const& pi, int n) {
  vector<int> ans(n + 1);
  for (int i = 0; i < n; i++) ans[pi[i]]++;
  for (int i = n - 1; i > 0; i--) ans[pi[i - 1]] += ans[i];
  for (int i = 0; i <= n; i++) ans[i]++;
  return ans;
}
// compression, if k = n - pi[n-1], divides n then 'k' is smallest
// unit to compress the string 's';
// aut[i][j] = automaton going from state 'i' with character 'j';
void compute_automaton(string s, vector<vector<int>>& aut) {
  s += '#';
  int n = s.size();
  vector<int> pi = prefix_function(s);
  aut.assign(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i])
        aut[i][c] = aut[pi[i - 1]][c];
      else
        aut[i][c] = i + ('a' + c == s[i]);
    }
  }
}