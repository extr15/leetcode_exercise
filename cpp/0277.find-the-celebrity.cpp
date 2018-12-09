int getId(int M[MAX][MAX], int n) {
  int normal_cnt = 0;
  bool* maybe_cele = new bool[n];
  for (int i = 0; i < n; i++) {
    maybe_cele[i] = true;
  }
  for (int i = 0; i < n; i++) {
    if (!maybe_cele[i]) {
      continue;
    }
    bool cur_cele = true;
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      if (M[i][j] == 1) {
        cur_cele = false;
        maybe_cele[i] = false;
        normal_cnt++;
        break;
      } else {
        if (maybe_cele[j]) {
          maybe_cele[j] = false;
          normal_cnt++;
        }
      }
    }
    if (normal_cnt >= n) {
      return -1;
    }
  }
  for (int i = 0; i < n; i++) {
    if (!maybe_cele[i]) {
      continue;
    }
    bool not_be_known = false;
    for (int j = 0; j < n; j++) {
      if (i != j && M[j][i] == 0) {
        not_be_known = true;
        break;
      }
    }
    if (!not_be_known) {
      return i;
    }
  }
  return -1;
}

// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
 public:
  int findCelebrity(int n) {
    int normal_cnt = 0; // 记录普通人的数目
    bool* maybe_cele = new bool[n];
    for (int i = 0; i < n; i++) {
      maybe_cele[i] = true;
    }
    for (int i = 0; i < n; i++) {
      if (!maybe_cele[i]) {
        continue;
      }
      bool cur_cele = true;
      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }
        if (knows(i, j) == 1) {
          cur_cele = false;
          maybe_cele[i] = false;
          normal_cnt++;
          break;
        } else {
          if (maybe_cele[j]) {
            maybe_cele[j] = false;
            normal_cnt++;
          }
        }
      }
      if (normal_cnt >= n) {
        return -1;
      }
    }
    for (int i = 0; i < n; i++) {
      if (!maybe_cele[i]) {
        continue;
      }
      bool not_be_known = false;
      for (int j = 0; j < n; j++) {
        if (i != j && knows(j, i) == 0) {
          not_be_known = true;
          break;
        }
      }
      if (!not_be_known) {
        return i;
      }
    }
    return -1;
  }
};
