class Solution {
 public:
  bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
    const int n = org.size();
    unordered_map<int, unordered_set<int>> num_to_larger_num;
    unordered_map<int, int> num_to_pre_cnt;
    unordered_set<int> free_num;
    for (auto& s : seqs) {
      if(s.size() > n) {
        return false;
      }
      if (s.empty()) {
        continue;
      }
      if (s.size() == 1) {
        free_num.insert(s[0]);
        continue;
      }
      if (num_to_pre_cnt.find(s[0]) == num_to_pre_cnt.end()) {
        num_to_pre_cnt.emplace(s[0], 0);
      }
      for (int i = 0; i < s.size() - 1; i++) {
        if(s[i] == s[i+1]) {
          return false;
        }
        auto& larger = num_to_larger_num[s[i]];
        if (larger.find(s[i + 1]) == larger.end()) {
          larger.insert(s[i + 1]);
          num_to_pre_cnt[s[i + 1]]++;
        }
        if(num_to_larger_num[s[i+1]].find(s[i]) != num_to_larger_num[s[i+1]].end()) {
          return false;
        }
      }
    }
    vector<int> order_num;
    queue<int> q;
    for (auto& pre : num_to_pre_cnt) {
      free_num.erase(pre.first);
      if (pre.second == 0) {
        q.push(pre.first);
      }
    }
    if (free_num.size() + q.size() > 1) {
      return false;
    }
    if(free_num.size() == 1) {
      order_num.push_back(*free_num.begin());
    }
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      order_num.push_back(cur);
      auto larger = num_to_larger_num[cur];
      for (auto num : larger) {
        num_to_pre_cnt[num]--;
        if (num_to_pre_cnt[num] == 0) {
          q.push(num);
        }
      }
      if (q.size() > 1) {
        return false;
      }
    }
    for(auto& pre : num_to_pre_cnt) {
      if(pre.second != 0) {
        return false;
      }
    }
    if (order_num != org) {
      return false;
    } else {
      return true;
    }
  }
};
