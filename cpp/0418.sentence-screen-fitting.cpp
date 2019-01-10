#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TLE.
class Solution2 {
 public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    const int n = sentence.size();
    int cnt = 0;
    int r = 0, c = 0;
    int i = 0;
    while (r < rows) {
      while (i < n && c + sentence[i].size() <= cols) {
        c += sentence[i].size();
        c += 1;
        i++;
      }
      if (i == n) {
        i = 0;
        cnt++;
        continue;
      }
      r++;
      c = 0;
    }
    return cnt;
  }
};

// AC.
class Solution3 {
 public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    const int n = sentence.size();
    int cnt = 0;
    int r = 0, c = 0;
    int i = 0;
    while (r < rows) {
      while (i < n && c + sentence[i].size() <= cols) {
        c += sentence[i].size();
        c += 1;
        i++;
      }
      if (i == n) {
        if (c == cols || c == cols + 1) {
          int left_seg = rows / (r + 1);
          cnt = left_seg * (cnt + 1);
          r = rows - (rows % (r + 1));
          c = 0;
        } else {
          cnt++;
        }
        i = 0;
        continue;
      }
      r++;
      c = 0;
    }
    return cnt;
  }
};

// AC.
class Solution4 {
 public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    const int n = sentence.size();
    int cnt = 0;
    int r = 0, c = 0;
    int i = 0;
    bool first_time = true;
    while (r < rows) {
      while (i < n && c + sentence[i].size() <= cols) {
        c += sentence[i].size();
        c += 1;
        i++;
      }
      if (i == n) {
        if (c == cols || c == cols + 1) {
          int left_seg = rows / (r + 1);
          cnt = left_seg * (cnt + 1);
          r = rows - (rows % (r + 1));
          c = 0;
        } else {
          cnt++;
          if (r == 0 && first_time) {
            int seg = cols / c;
            cnt = seg;
            c = cols - (cols % c);
            first_time = false;
          }
        }
        i = 0;
        continue;
      }
      r++;
      c = 0;
    }
    return cnt;
  }
};

// AC.
class Solution {
 public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    const int n = sentence.size();
    string all_word;
    for (int i = 0; i < n; i++) {
      all_word += sentence[i] + " ";
    }
    const int len = all_word.size();
    int i = 0, r = 0, c = 0;
    int capacity = 0;
    if (cols > len) {
      capacity += (int(cols / len)) * len * rows;
      cols = cols % len;
      if(cols == 0) {
        return capacity / len;
      }
    }
    while (r < rows) {
      int cur_col = cols;
      if (all_word[(i + cur_col - 1) % len] != ' ' && all_word[(i + cur_col) % len] != ' ') {
        while (cur_col > 0 && all_word[(i + cur_col - 1) % len] != ' ') {
          cur_col--;
        }
      }
      else if(all_word[(i + cur_col) % len] == ' ') {
        cur_col++;
      }
      if(cur_col == 0) {
        break;
      }
      //cout << "cur_col: " << cur_col << endl;
      capacity += cur_col;
      i = (i + cur_col) % len;
      r++;
    }
    //cout << "capacity: " << capacity << endl;
    int cnt = capacity / len;
    return cnt;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  vector<string> sentence;

//  sentence.push_back("f");
//  sentence.push_back("g");
//  sentence.push_back("p");
//  cout << sol.wordsTyping(sentence, 8, 7) << endl;

//  sentence.push_back("h");
//  cout << sol.wordsTyping(sentence, 100, 100) << endl;

  sentence.push_back("hello");
  cout << sol.wordsTyping(sentence, 10000, 1) << endl;

//  sentence.push_back("I");
//  sentence.push_back("had");
//  sentence.push_back("apple");
//  sentence.push_back("pie");
//  cout << sol.wordsTyping(sentence, 4, 5) << endl;
  return 0;
}

