class Solution {
 public:
  void reverseWords(vector<char>& str, int i, int j) {
    while (i < j) {
      std::swap(str[i], str[j]);
      i++;
      j--;
    }
  }
  void reverseWords(vector<char>& str) {
    if (str.size() < 3) {
      return;
    }
    const int n = str.size();
    reverseWords(str, 0, n - 1);

    int i = 0;
    int j = 0;
    while (i < n) {
      while (j < n && str[j] != ' ') {
        j++;
      }
      reverseWords(str, i, j - 1);
      j++;
      i = j;
    }
  }
};
