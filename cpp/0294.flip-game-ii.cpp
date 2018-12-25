// AC.
class Solution {
public:
    bool canWin(string s) {
      const int n = s.length();
      for(int i=0;i<n-1;i++) {
        if(s[i]=='+' && s[i+1] == '+') {
          s[i] = s[i+1] = '-';
          if(!canWin(s)) {
            return true;
          }
          s[i] = s[i+1] = '+';
        }
      }
      return false;
    }
};
