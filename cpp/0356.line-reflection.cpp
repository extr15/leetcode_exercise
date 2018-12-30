// Wrong understanding.
class Solution {
 public:
  bool isReflected(vector<pair<int, int>>& points) {
    const int n = points.size();
    if (n == 0) {
      return true;
    }
    int sum_x = 0;
    for (auto& p : points) {
      p.first *= 2;
      sum_x += p.first;
    }
    if (sum_x % n != 0) {
      return false;
    }
    int mean_x = sum_x / n;
    unordered_map<int, unordered_set<int>> y_to_delta_x;
    for (auto& p : points) {
      int y = p.second;
      int dx = p.first - mean_x;
      if (dx == 0) {
        continue;
      }
      if (y_to_delta_x.find(y) != y_to_delta_x.end()) {
        auto& delta_x = y_to_delta_x[y];
        if (delta_x.find(-dx) != delta_x.end()) {
          delta_x.erase(-dx);
        } else {
          delta_x.insert(dx);
        }
      } else {
        y_to_delta_x[y].insert(dx);
      }
    }
    for (auto& elem : y_to_delta_x) {
      if (elem.second.size() != 0) {
        return false;
      }
    }
    return true;
  }
};

// AC.
class Solution {
 public:
  bool isReflected(vector<pair<int, int>>& points) {
    const int n = points.size();
    if (n == 0) {
      return true;
    }
    unordered_map<int, unordered_set<int>> y_to_delta_x;
    for (auto& p : points) {
      int y = p.second;
      p.first *= 2;
      y_to_delta_x[y].insert(p.first);
    }
    bool mean_set = false;
    int last_mean;
    for (auto& elem : y_to_delta_x) {
      int sum_x = 0;
      auto& x_set = elem.second;
      for (auto& x : x_set) {
        sum_x += x;
      }
      const int x_num = x_set.size();
      if (sum_x % x_num != 0) {
        return false;
      }
      int mean_x = sum_x / x_num;
      if (!mean_set) {
        mean_set = true;
        last_mean = mean_x;
      } else {
        if (mean_x != last_mean) {
          return false;
        }
      }
      unordered_set<int> dx_set;
      for (auto x : x_set) {
        int dx = x - mean_x;
        if(dx == 0) {
          continue;
        }
        if (dx_set.find(-dx) != dx_set.end()) {
          dx_set.erase(-dx);
        } else {
          dx_set.insert(dx);
        }
      }
      if (!dx_set.empty()) {
        return false;
      }
    }
    return true;
  }
};

// AC
// unordered_set<Coord> with PairHash.
struct PairHash {
  template<typename T, typename U>
  std::size_t operator()(const std::pair<T, U>& x) const {
    return (std::hash<T>()(x.first) ^ std::hash<U>()(x.second));
  }
};

class Solution {
 public:
   typedef pair<int, int> Coord;
  bool isReflected(vector<Coord>& points) {
    const int n = points.size();
    if(n==0) {
      return true;
    }
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    unordered_set<Coord, PairHash> pt_set;
    for(auto& p : points) {
      min_x = min(min_x, p.first);
      max_x = max(max_x, p.first);
      pt_set.insert(p);
    }
    int sum = min_x + max_x;
    for(auto& p : pt_set) {
      int x2 = sum - p.first;
      Coord pt2 = make_pair(x2, p.second);
      if(pt_set.find(pt2) == pt_set.end()) {
        return false;
      }
    }
    return true;
  }
};

