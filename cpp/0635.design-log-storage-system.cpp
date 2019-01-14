#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

// AC.
class LogSystem {
 public:
  LogSystem() {}

  void put(int id, string timestamp) { timestamp_to_id.insert({timestamp, id}); }

  vector<int> retrieve(string s, string e, string gra) {
    int comp_len = 4;
    if (gra == "Year") {
      comp_len = 4;
    } else if (gra == "Month") {
      comp_len = 7;
    } else if (gra == "Day") {
      comp_len = 10;
    } else if (gra == "Hour") {
      comp_len = 13;
    } else if (gra == "Minute") {
      comp_len = 16;
    } else if (gra == "Second") {
      comp_len = 19;
    }
    // auto begin = timestamp_to_id.lower_bound(s.substr(0, comp_len), );
    auto it = timestamp_to_id.begin();
    auto prev_it = it;
    const string start = s.substr(0, comp_len);
    while (it != timestamp_to_id.end() && it->first.substr(0, comp_len) < start) {
      prev_it = it;
      it++;
    }
    auto start_it = it;
    const string end = e.substr(0, comp_len);
    while (it != timestamp_to_id.end() && it->first.substr(0, comp_len) <= end) {
      it++;
    }
    auto end_it = it;
    vector<int> res;
    for (auto it2 = start_it; it2 != end_it; it2++) {
      res.push_back(it2->second);
    }
    return res;
  }

 private:
  map<string, int> timestamp_to_id;
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */


int main(int argc, char *argv[]) {
  
    return 0;
}
