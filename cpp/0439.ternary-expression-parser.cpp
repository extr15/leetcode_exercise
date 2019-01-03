class Solution {
 public:
  string parseTernary(string expression) {
    if (expression.size() == 1) {
      return expression;
    }
    int i = 0;
    if (expression[0] == 'T' || expression[0] == 'F') {
      int j = 1;
      int question_cnt = 0;
      int colon_cnt = 0;
      while (1) {
        if (expression[j] == '?') {
          question_cnt++;
        } else if (expression[j] == ':') {
          colon_cnt++;
        }
        if (colon_cnt == question_cnt) {
          break;
        }
        j++;
      }
      if (expression[0] == 'T') {
        string s = expression.substr(2, j - 2);
        return parseTernary(s);
      } else {
        string s = expression.substr(j + 1, expression.size() - j - 1);
        return parseTernary(s);
      }
    }
  }
};
