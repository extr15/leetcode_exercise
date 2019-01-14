#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;
// AC.
class AutocompleteSystem1 {
 private:
  struct Node {
    Node(string s, int t) : str(s), times(t){};
    string str;
    int times;
    bool operator<(const Node& rhs) const {
      if (times != rhs.times) {
        return times < rhs.times;
      } else {
        return str > rhs.str;
      }
    }
  };

 public:
  AutocompleteSystem1(vector<string> sentences, vector<int> times) : cur_str(""), cur_len(0) {
    const int n = sentences.size();
    for (int i = 0; i < n; i++) {
      str_to_times.emplace(sentences[i], times[i]);
    }
  }

  vector<string> input(char c) {
    vector<string> res;
    const int kMaxCnt = 3;
    if (c != '#') {
      cur_str += c;
      cur_len++;
      if (cur_len == 1) {
        for (auto& s : str_to_times) {
          if (c == s.first[0]) {
            matched_str.push(Node(s.first, s.second));
          }
        }
      }
      // not `else if`, since we also need to return some matched string when the first time.
      if (!matched_str.empty()) {
        priority_queue<Node> next_match;
        while (!matched_str.empty()) {
          Node cur = matched_str.top();
          matched_str.pop();
          if (cur.str.substr(0, cur_len) == cur_str) {
            next_match.push(cur);
            if (res.size() < kMaxCnt) {
              res.push_back(cur.str);
            }
          }
        }
        swap(matched_str, next_match);
      }
    } else {
      if (cur_len > 0) {
        str_to_times[cur_str]++;
      }
      cur_str = "";
      cur_len = 0;

      // Don't forget to clear `matched_str`.
      // priority_queue don't have a `clear()` function.
      // matched_str.clear();
      priority_queue<Node> empty_q;
      swap(matched_str, empty_q);
    }
    return res;
  }

 private:
  map<string, int> str_to_times;
  string cur_str;
  int cur_len;
  priority_queue<Node> matched_str;
};

// AC.
class AutocompleteSystem {
 private:
  struct Node {
    Node(string s, int t) : str(s), times(t){};
    string str;
    int times;
  };
  struct NodeCmp {
    //bool operator()(const Node*& n1, const Node*& n2) const {
    //bool operator()(Node* const & n1, Node* const & n2) const {
    //bool operator()(Node* n1, Node* n2) const {
    bool operator()(const Node* n1, const Node* n2) const {
      if (n1->times != n2->times) {
        return n1->times < n2->times;
      } else {
        return n1->str > n2->str;
      }
    }
  };
  typedef priority_queue<Node*, vector<Node*>, NodeCmp> PriorityQ;

 public:
  AutocompleteSystem(vector<string> sentences, vector<int> times) : cur_str(""), cur_len(0) {
    const int n = sentences.size();
    for (int i = 0; i < n; i++) {
      // assume no duplicate in `sentences`.
      Node* node = new Node(sentences[i], times[i]);
      strs.push_back(node);
    }
  }
  vector<string> input(char c) {
    vector<string> res;
    const int kMaxCnt = 3;
    if (c != '#') {
      cur_str += c;
      cur_len++;
      if (cur_len == 1) {
        for (auto& n : strs) {
          if (n->str[0] == c) {
            matched_str.push(n);
          }
        }
      }
      if (!matched_str.empty()) {
        PriorityQ next_match;
        while (!matched_str.empty()) {
          Node* cur = matched_str.top();
          matched_str.pop();
          if (cur->str.substr(0, cur_len) == cur_str) {
            next_match.push(cur);
            if (res.size() < kMaxCnt) {
              res.push_back(cur->str);
            }
          }
        }
        swap(matched_str, next_match);
      }
    } else {
      bool is_new_str = true;
      while (!matched_str.empty()) {
        Node* cur = matched_str.top();
        matched_str.pop();
        if (cur->str == cur_str) {
          is_new_str = false;
          cur->times++;
        }
      }
      if (is_new_str) {
        Node* node = new Node(cur_str, 1);
        strs.push_back(node);
      }
      cur_str = "";
      cur_len = 0;
    }
    return res;
  }

 private:
  PriorityQ matched_str;
  vector<Node*> strs;
  string cur_str;
  int cur_len;
};
/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj.input(c);
 */

/**
Input
["AutocompleteSystem","input","input","input","input"]
[[["i love you","island","iroman","i love leetcode"],[5,3,2,2]],["i"],[" "],["a"],["#"]]

Expected
[null,["i love you","island","i love leetcode"],["i love you","i love leetcode"],[],[]]
 */

/**
Input
["AutocompleteSystem", "input", "input", "input", "input", "input", "input", "input", "input",
"input", "input", "input", "input"]
[[ [ "i love you", "island", "iroman", "i love leetcode" ], [ 5, 3, 2, 2 ] ], ["i"], [" "], ["a"],
["#"], ["i"], [" "], ["a"], ["#"], ["i"], [" "], ["a"], ["#"]]

Expected
[null, [ "i love you", "island", "i love leetcode" ], [ "i love you", "i love leetcode" ], [], [], [
"i love you", "island", "i love leetcode" ], [ "i love you", "i love leetcode", "i a" ], ["i a"],
[], [ "i love you", "island", "i a" ], [ "i love you", "i a", "i love leetcode" ], ["i a"], []]
 */

int main(int argc, char* argv[]) { return 0; }
