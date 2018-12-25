class Solution {
 public:
  typedef pair<int, int> Coord;
  vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    unordered_map<int, vector<Coord>> island_id_to_coord;
    map<Coord, int> coord_to_island_id;
    int island_id = 0;
    vector<Coord> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, +1}};
    vector<int> res;
    for (auto& p : positions) {
      if (coord_to_island_id.find(p) != coord_to_island_id.end()) {
        continue;
      }
      unordered_set<int> merge_island_id;
      for (auto& dir : dirs) {
        int x = p.first + dir.first;
        int y = p.second + dir.second;
        if (x < 0 || x >= m || y < 0 || y >= n) {
          continue;
        }
        Coord next_p(x, y);
        if (coord_to_island_id.find(next_p) != coord_to_island_id.end()) {
          merge_island_id.insert(coord_to_island_id[next_p]);
        }
      }
      if (merge_island_id.empty()) {
        island_id_to_coord[island_id].push_back(p);
        coord_to_island_id.insert({p, island_id});
        island_id++;
      } else {
        int min_id = *std::min_element(merge_island_id.begin(), merge_island_id.end());
        for (auto id : merge_island_id) {
          if (id != min_id) {
            for (auto coord : island_id_to_coord[id]) {
              coord_to_island_id[coord] = min_id;
              island_id_to_coord[min_id].push_back(coord);
            }
            island_id_to_coord.erase(id);
          }
        }
        island_id_to_coord[min_id].push_back(p);
        coord_to_island_id.insert({p, min_id});
      }
      res.push_back(island_id_to_coord.size());
    }
    return res;
  }
};
