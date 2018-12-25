class Solution {
 public:
  int minCost(vector<vector<int>>& costs) {
    const int n = costs.size();
    vector<int> last_total_cost{0, 0, 0};
    vector<int> cur_total_cost(3);
    int min_cost_so_far[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
      const vector<int>& cur = costs[i];
      cur_total_cost[0] = min(last_total_cost[1] + cur[0], last_total_cost[2] + cur[0]);
      cur_total_cost[1] = min(last_total_cost[0] + cur[1], last_total_cost[2] + cur[1]);
      cur_total_cost[2] = min(last_total_cost[1] + cur[2], last_total_cost[0] + cur[2]);
      last_total_cost = cur_total_cost;
    }
    return min(min(cur_total_cost[0], cur_total_cost[1]), cur_total_cost[2]);
  }
};
