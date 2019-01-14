class Solution {
 public:
  bool repeatedSubstringPattern(string s) {
    const int n = s.size();
    int divide = 2;
    while (divide <= n) {
      if (n % divide == 0) {
        int len = n / divide;
        string pattern = s.substr(0, len);
        bool is_equal = true;
        for (int i = 1; i < divide; i++) {
          if (pattern != s.substr(i * len, len)) {
            is_equal = false;
            break;
          }
        }
        if (is_equal) {
          return true;
        }
      }
      divide++;
    }
    return false;
  }
};

vector<int> calcNext(const string& s) {
  vector<int> next(n, -1);
  const int n = s.size();
  next[0] = -1;
  int j = 0;
  int k = -1;
  while (j < n -1) {
    if (k == -1 || p[j] == p[k]) {
      k++;
      j++;
      next[j] = k;
    } else {
      k = next[k];
    }
  }
  return next;
}

vector<int> calcNext_v2(const string& s) {
  vector<int> next(n, -1);
  const int n = s.size();
  next[0] = -1;
  int j = 0;
  int k = -1;
  while (j < n-1) {
    if (k == -1 || p[j] == p[k]) {
      k++;
      j++;
      if(p[j] != p[k]) {
        next[j] = k;
      }
      else {
        next[j] = next[k];
      }
    } else {
      k = next[k];
    }
  }
  return next;
}

int kmpSearch(const string& s, const string& p) {
  const int m = s.size();
  const int n = p.size();
  int i = 0, j = 0;
  while (i < m && j < n) {
    if (j == -1 || s[i] == p[j]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }
  if (j == n) {
    return i - j;
  } else {
    return -1;
  }
}

int kmpSearch(const string& s, const string& p) {
  int i = 0, j = 0;
  const int m = s.size();
  const int n = p.size();
  while(i < m && j < n) {
    if(j==-1 || s[i] == p[j]) {
      i++;
      j++;
    }
    else {
      j = next[j];
    }
  }
}

vector<int> calcNext(const string& p) {
  const int n = p.size();
  vector<int> next(n, -1);
  next[0] = -1;
  int j = 0;
  int k = -1;
  while(j < n -1) {
    if(k==-1 || p[j] == p[k]) {
      k++;
      j++;
      if(p[j] != p[k]) {
        next[j] = k;
      }
      else {
        next[j] = next[k];
      }
    }
    else {
      k = next[k];
    }
  }
}
