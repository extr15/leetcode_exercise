class Solution {
 public:
  string appendFlipString(const string& s, bool is_odd) {
    const int n = s.size();
    // string res((is_odd?) 2*n -1 : 2*n);
    string res(s);
    int res_n = (is_odd ? 2 * n - 1 : 2 * n);
    for (int j = n; j < res_n; j++) {
      int i = res_n - 1 - j;
      if (s[i] == '0' || s[i] == '1' || s[i] == '8') {
        res += s[i];
      } else if (s[i] == '6') {
        res += '9';
      } else if (s[i] == '9') {
        res += '6';
      }
    }
    return res;
  }
  void generateDigitString(const vector<string>& digit, int n, const string& s, vector<string>& v,
                           bool is_odd) {
    if (n == 0) {
      // skip the number with leading zero, ex: "00" is invalid.
      // but when n=1, "0" is valid: if (s[0] != '0' || (is_odd &&s.size() == 1))
      if (s[0] != '0') {
        v.push_back(appendFlipString(s, is_odd));
      }
      return;
    }
    for (auto d : digit) {
      if (is_odd && n == 1) {
        if (d == "6" || d == "9") {
          continue;
        }
      }
      generateDigitString(digit, n - 1, s + d, v, is_odd);
    }
  }
  vector<string> findStrobogrammatic(int n) {
    vector<string> res;
    if (n <= 0) {
      return res;
    }
    const bool is_odd = (n % 2 == 1);
    int half_n = n / 2;
    if (is_odd) {
      half_n++;
    }
    res.reserve(pow(5, half_n));
    vector<string> digit{"0", "1", "8", "6", "9"};
    if (n == 1) {
      res.push_back("0");
    }
    generateDigitString(digit, half_n, "", res, is_odd);
    return res;
  }
};

class Solution {
 public:
  void helper(char* ch, int left, int right, vector<string>& res) {
    if (left > right) {
      res.push_back(string(ch));
      return;
    }
    if (left == right) {
      ch[left] = '0';
      res.push_back(string(ch));
      ch[left] = '1';
      res.push_back(string(ch));
      ch[left] = '8';
      res.push_back(string(ch));
      return;
    }
    if (left != 0) {
      ch[left] = ch[right] = '0';
      helper(ch, left + 1, right - 1, res);
    }
    ch[left] = ch[right] = '1';
    helper(ch, left + 1, right - 1, res);
    ch[left] = ch[right] = '8';
    helper(ch, left + 1, right - 1, res);
    ch[left] = '6';
    ch[right] = '9';
    helper(ch, left + 1, right - 1, res);
    ch[left] = '9';
    ch[right] = '6';
    helper(ch, left + 1, right - 1, res);
  }
  vector<string> findStrobogrammatic(int n) {
    char* ch = new char[n + 1];
    ch[n] = '\0';
    vector<string> res;
    helper(ch, 0, n - 1, res);
    return res;
  }
};
