class Solution {
public:
    string getHint(string secret, string guess) {
      vector<int> digits_cnt1(10, 0);
      vector<int> digits_cnt2(10, 0);
      const int n = secret.length();
      int bulls_num = 0, cows_num = 0;
      for(int i=0; i<n; i++) {
        if(secret[i] == guess[i]) {
          bulls_num++;
        }
        else {
          digits_cnt1[secret[i] - '0']++;
          digits_cnt2[guess[i] - '0']++;
        }
      }
      for(int i=0;i<10;i++) {
        cows_num += std::min(digits_cnt1[i], digits_cnt2[i]);
      }
      stringstream ss;
      ss << bulls_num << "A" << cows_num << "B";
      return ss.str();
    }
};
