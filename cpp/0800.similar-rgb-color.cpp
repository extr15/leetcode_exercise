class Solution {
 public:
  int findMostSimilar(int color) {
    int min_delta = std::numeric_limits<int>::max();
    int min_idx = 0;
    for (int i = 0; i < 16; i++) {
      int cur = i * 16 + i;
      int delta = std::abs(cur - color);
      if (delta < min_delta) {
        min_delta = delta;
        min_idx = i;
      }
    }
    return min_idx;
  }
  int convertCharToInt(char c) {
    if (c >= '0' && c <= '9') {
      return c - '0';
    } else {
      return (10 + (c - 'a'));
    }
  }
  string similarRGB(string color) {
    string res("#");
    for (int i = 0; i < 3; i++) {
      int hi = convertCharToInt(color[1 + 2 * i]);
      int lo = convertCharToInt(color[2 + 2 * i]);
      int cur_color = hi * 16 + lo;
      int idx = findMostSimilar(cur_color);
      if (idx <= 9) {
        char ch = (idx + '0');
        res += ch;
        res += ch;
      } else {
        char ch = (idx - 10 + 'a');
        res += ch;
        res += ch;
      }
    }
    return res;
  }
};
