class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
      const int n = gas.size();
      int cur_gas = 0;
      int total_gas = 0;
      int start_idx = 0;
      for(int i=0; i<n; i++) {
        int delta = gas[i] - cost[i];
        if(cur_gas + delta >=0) {
          cur_gas += delta;
        }
        else {
          start_idx = i+1;
          cur_gas = 0;
        }
        total_gas += delta;
      }
      if(total_gas >= 0) {
        return start_idx;
      }
      else {
        return -1;
      }
    }
};
