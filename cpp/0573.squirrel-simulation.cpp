class Solution {
 public:
  int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel,
                  vector<vector<int>>& nuts) {
    int sum_dist_tree_to_nuts = 0;
    int max_tree_nut_subtract_nut_squirrel = std::numeric_limits<int>::min();
    for (auto& cur : nuts) {
      const int tree_nut = (abs(cur[0] - tree[0]) + abs(cur[1] - tree[1]));
      sum_dist_tree_to_nuts += tree_nut;
      const int nut_squirrel = abs(cur[0] - squirrel[0]) + abs(cur[1] - squirrel[1]);
      int delta = tree_nut - nut_squirrel;
      max_tree_nut_subtract_nut_squirrel = max(max_tree_nut_subtract_nut_squirrel, delta);
    }
    return (2 * sum_dist_tree_to_nuts - max_tree_nut_subtract_nut_squirrel);
  }
};
