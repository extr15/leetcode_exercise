
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
 public:
  typedef pair<int, vector<int>> Node;
  struct NodeCmp {
    bool operator()(const Node& n1, const Node& n2) { return n1.first > n2.first; }
  };
  vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    const int n = points.size();
    vector<int> dist(n);
    //vector<pair<int, vector<int>>> dist_to_pt(n);
    priority_queue<Node, vector<Node>, NodeCmp> pq;
    for (auto& p : points) {
      int dist = p[0] * p[0] + p[1] * p[1];
      // dist_to_pt.emplace(dist, p);
      pq.push({dist, p});
    }
    vector<vector<int>> res;
    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();
      res.push_back(cur.second);
      if (res.size() >= K) {
        break;
      }
    }
    return res;
  }
};

int main(int argc, char* argv[]) { return 0; }
