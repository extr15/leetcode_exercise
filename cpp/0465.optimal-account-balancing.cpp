// Wrong understanding.
class Solution {
 public:
  int minTransfers(vector<vector<int>>& transactions) {
    unordered_map<int, int> id_to_val;
    unordered_map<int, unordered_set<int> > id_to_adjacent;
    unordered_set<int> all_id;
    for (auto& t : transactions) {
      int first = t[0];
      int second = t[1];
      id_to_val[first] -= t[2];
      id_to_val[second] += t[2];
      id_to_adjacent[first].insert(second);
      id_to_adjacent[second].insert(first);
      all_id.insert(first);
      all_id.insert(second);
    }
    vector<unordered_set<int>> connected_id;
    while(!all_id.empty()) {
      int cur = *all_id.begin();
      queue<int> q;
      q.push(cur);
      all_id.erase(cur);
      unordered_set<int> connect;
      connect.insert(cur);
      while(!q.empty()) {
        int now = q.front();
        q.pop();
        for(auto& adj : id_to_adjacent[now]) {
          if(all_id.count(adj)) {
            all_id.erase(adj);
            q.push(adj);
            connect.insert(adj);
          }
        }
      }
      connected_id.push_back(connect);
    }
    int min_transaction_cnt = 0;
    for(auto& connect : connected_id) {
      int non_zero_cnt = 0;
      for(int id : connect) {
        if(id_to_val[id] != 0) {
          non_zero_cnt++;
        }
      }
      min_transaction_cnt += max(non_zero_cnt-1, 0);
    }
    return min_transaction_cnt;

//    int non_zero_cnt = 0;
//    for (auto& v : id_to_val) {
//      if (v.second != 0) {
//        non_zero_cnt++;
//      }
//    }
//    return max(non_zero_cnt - 1, 0);
  }
};
