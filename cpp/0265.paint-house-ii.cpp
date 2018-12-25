class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
      const int n = costs.size();
      if(n == 0) {
        return 0;
      }
      const int k = costs[0].size();
      vector<int> last_min_total_costs(k), tmp_cost(k);
      last_min_total_costs = costs[0];
      for(int i=1; i<n; i++) {
        int min_cost_idx = 0, second_min_cost_idx = 1;
        if(last_min_total_costs[0] > last_min_total_costs[1]) {
          swap(min_cost_idx, second_min_cost_idx);
        }
        for(int j=2;j<k;j++) {
          if(last_min_total_costs[j] < last_min_total_costs[min_cost_idx]) {
            second_min_cost_idx = min_cost_idx;
            min_cost_idx = j;
          }
          else if(last_min_total_costs[j] < last_min_total_costs[second_min_cost_idx]) {
            second_min_cost_idx = j;
          }
        }
        for(int j=0;j<k;j++) {
          if(j != min_cost_idx) {
            tmp_cost[j] = costs[i][j] + last_min_total_costs[min_cost_idx];
          }
          else {
            tmp_cost[j] = costs[i][j] + last_min_total_costs[second_min_cost_idx];
          }
        }
        last_min_total_costs = tmp_cost;
      }
      return *std::min_element(last_min_total_costs.begin(), last_min_total_costs.end());
    }
};
