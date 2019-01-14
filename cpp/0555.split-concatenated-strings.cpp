#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

// Wrong understanding.
class Solution1 {
 public:
  string splitLoopedString(vector<string>& strs) {
    string cur;
    int break_idx;
    vector<int> lens;
    char max_ch = 'a';
    vector<int> char_to_str_idx;
    vector<int> char_to_first_idx;
    vector<int> char_to_last_idx;
    int str_idx = 0;
    int ch_idx = 0;
    unordered_set<int> max_ch_idx;
    string total_str;
    total_str.reserve(1000);
    for (const auto& s : strs) {
      const int len = s.size();
      lens.push_back(len);
      total_str += s;
      int first_idx = ch_idx;
      int last_idx = ch_idx + len - 1;
      for (auto& c : s) {
        if (c > max_ch) {
          max_ch = c;
          max_ch_idx.clear();
          max_ch_idx.insert(ch_idx);
        } else if (c == max_ch) {
          max_ch_idx.insert(ch_idx);
        }
        char_to_str_idx.push_back(str_idx);
        char_to_first_idx.push_back(first_idx);
        char_to_last_idx.push_back(last_idx);
        ch_idx++;
      }
      str_idx++;
    }
    int total_len = ch_idx;
    struct Elem {
      Elem() : cur_len(0), direction(0), cur_string(""){};
      int cur_len;
      int direction;   // 0: not determine, -1: left, 1: right.
      int left_order;  // 0: not determine, -1: reverse order, 1: order.
      int right_order;
      string cur_string;
    };
    // unordered_map<max_ch_idx, pair<direction, cur_string> >.
    unordered_map<int, Elem> idx_to_elem;
    while (max_ch_idx.size() > 1) {
      char max_char = 'a';
      for (auto& ch_idx : max_ch_idx) {
        auto& elem = idx_to_elem[ch_idx];
        if (elem.cur_len == 0) {
          elem.cur_string += total_str[ch_idx];
          elem.cur_len = 1;
        } else {
          int left = ch_idx - elem.cur_len;
          if (left < 0) {
            left += total_len;
          }
//          if () {
//          }
          int right = ch_idx + elem.cur_len;
          if (right >= total_len) {
            right -= total_len;
          }
          bool select_left = false, select_right = false;
          if (elem.direction == -1 || (elem.direction == 0 && total_str[left] > total_str[right])) {
            select_left = true;
          } else if (elem.direction == 1 ||
                     (elem.direction == 0 && total_str[left] < total_str[right])) {
            select_right = true;
          }
          //          if (direction == 0) {
          //            if (total_str[left] > total_str[right]) {
          //              select_left = true;
          //            } else if (total_str[left] < total_str[right]) {
          //              select_right = true;
          //            } else {
          //              elem.cur_string += total_str[left];
          //              elem.cur_len++;
          //            }
          //          } else if (direction == -1) {
          //            select_left = true;
          //          } else if (direction == 1) {
          //            select_right = true;
          //          }

          if (select_left) {
            elem.cur_string += total_str[left];
            elem.cur_len++;
            elem.direction = -1;
          } else if (select_right) {
            elem.cur_string += total_str[right];
            elem.cur_len++;
            elem.direction = 1;
          } else {
            elem.cur_string += total_str[left];
            elem.cur_len++;
          }
          if (elem.cur_string[elem.cur_len - 1] > max_char) {
            max_char = elem.cur_string[elem.cur_len - 1];
          }
        }
      }
      for (auto it = max_ch_idx.begin(); it != max_ch_idx.end();) {
        int ch_idx = *it;
        auto& elem = idx_to_elem[ch_idx];
        if (elem.cur_string[elem.cur_len - 1] != max_char) {
          it = max_ch_idx.erase(it);
        } else {
          it++;
        }
      }
    }
    //auto;
  }
};

// AC.
class Solution {
 public:
  string splitLoopedString(vector<string>& strs) {
    const int n = strs.size();
    vector<bool> reverse_larger;
    reverse_larger.reserve(n);
    vector<string> reversed_strs;
    reversed_strs.reserve(n);
    for (const auto& s : strs) {
      bool should_reverse = false;
      const int len = s.size();
      int i = 0, j = len - 1;
      while (i < j && s[i] == s[j]) {
        i++;
        j--;
      }
      if (i < j && s[i] < s[j]) {
        should_reverse = true;
      }
      reverse_larger.push_back(should_reverse);
      string tmp(s.crbegin(), s.crend());
      reversed_strs.push_back(tmp);
    }
    vector<string> left_str;
    for (int i = 0; i < n; i++) {
      string cur_str;
      for (int j = i + 1; j < n; j++) {
        if (reverse_larger[j]) {
          cur_str += reversed_strs[j];
        } else {
          cur_str += strs[j];
        }
      }
      for (int j = 0; j < i; j++) {
        if (reverse_larger[j]) {
          cur_str += reversed_strs[j];
        } else {
          cur_str += strs[j];
        }
      }
      left_str.push_back(cur_str);
      //cout << "i: " << i << ", left_str: " << left_str[i] << endl;
    }
    string res_str;
    for (int i = 0; i < n; i++) {
      const string& s = strs[i];
      const int len = s.size();
      char max_ch = 'a';
      vector<int> max_ch_idx;
      for (int j = 0; j < len; j++) {
        if (s[j] > max_ch) {
          max_ch_idx.clear();
          max_ch_idx.push_back(j);
          max_ch = s[j];
        } else if (s[j] == max_ch) {
          max_ch_idx.push_back(j);
        }
      }
      bool max_str_set = false;
      string max_str;
      for (auto j : max_ch_idx) {
        string cur_str = s.substr(j, len - j);
        //        const int left_len = left_str[i].size();
        //        if (j <= left_len) {
        //          cur_str += left_str[i].substr(0, j);
        //        } else {
        //          cur_str += left_str[i];
        //          cur_str += s.substr(0, j - left_len);
        //        }
        cur_str += left_str[i];
        cur_str += s.substr(0, j);
        //cout << "j: " << j << ", cur_str: " << cur_str << endl;
        if (!max_str_set) {
          max_str = cur_str;
          max_str_set = true;
        } else if (cur_str > max_str) {
          max_str = cur_str;
        }
      }
      const string& r_s = reversed_strs[i];
      for (auto j : max_ch_idx) {
        int r_j = len - 1 - j;
        string cur_str = r_s.substr(r_j, len - r_j);
        //        const int left_len = left_str[i].size();
        //        if (r_j <= left_len) {
        //          cur_str += left_str[i].substr(0, r_j);
        //        } else {
        //          cur_str += left_str[i];
        //          cur_str += s.substr(0, r_j - left_len);
        //        }
        cur_str += left_str[i];
        cur_str += r_s.substr(0, r_j);
        //cout << "r_j: " << r_j << ", cur_str: " << cur_str << endl;
        if (cur_str > max_str) {
          max_str = cur_str;
        }
      }
      if (res_str.empty()) {
        res_str = max_str;
      } else if (res_str < max_str) {
        res_str = max_str;
      }
    }
    return res_str;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  vector<string> strs{"abc", "zya"};
  cout << sol.splitLoopedString(strs) << endl;
  return 0;
}
