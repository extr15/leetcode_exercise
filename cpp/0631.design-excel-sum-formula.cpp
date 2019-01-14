#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Excel {
 public:
  Excel(int H, char W) : height(H), width(W) {}

  void clearDependCells(int idx) {
    //cout << "clearDependCells idx: " << idx << endl;
    auto& depend_cells = sum_cell_and_times[idx];
    for (auto& cell : depend_cells) {
      const int depend_idx = cell.first;
      //cout << "depend_idx: " << depend_idx << endl;
      affect[depend_idx].erase(idx);
    }
    depend_cells.clear();
  }
  inline void set(int idx, int v) {
    int r = getRow(idx);
    char c = getCol(idx);
    set(r, c, v);
  }
  void updateCell(int idx, int v) {
    const int delta = v - idx_to_val[idx];
    idx_to_val[idx] = v;
    // cout << "delta: " << delta << endl;
    if (delta != 0) {
      for (auto& cell : affect[idx]) {
        // cout << "cell: " << cell << endl;
        auto& depend_cells = sum_cell_and_times[cell];
        if (depend_cells.find(idx) != depend_cells.end()) {
          const int times = depend_cells[idx];
          // idx_to_val[cell] += times * delta;
          int new_val = idx_to_val[cell] + times * delta;
          // cout << "new_val: " << new_val << endl;
          updateCell(cell, new_val);
        }
      }
    }
  }
  void set(int r, char c, int v) {
    // cout << "set: " << r << ", " << c << endl;
    const int idx = getIdx(r, c);
    clearDependCells(idx);
    updateCell(idx, v);
  }
  void set_Wrong(int r, char c, int v) {
    // cout << "set: " << r << ", " << c << endl;
    const int idx = getIdx(r, c);
    clearDependCells(idx);
    const int delta = v - idx_to_val[idx];
    idx_to_val[idx] = v;
    // cout << "delta: " << delta << endl;
    if (delta != 0) {
      for (auto& cell : affect[idx]) {
        // cout << "cell: " << cell << endl;
        auto& depend_cells = sum_cell_and_times[cell];
        if (depend_cells.find(idx) != depend_cells.end()) {
          const int times = depend_cells[idx];
          // idx_to_val[cell] += times * delta;
          int new_val = idx_to_val[cell] + times * delta;
          // cout << "new_val: " << new_val << endl;
          set(cell, new_val);
        }
      }
    }
  }

  int get(int r, char c) {
    const int idx = getIdx(r, c);
    return idx_to_val[idx];
  }

  int sum(int r, char c, vector<string> strs) {
    if (strs.empty()) {
      return 0;
    }
    const int idx = getIdx(r, c);
    clearDependCells(idx);
    auto& depend_cells = sum_cell_and_times[idx];

    int new_val = 0;
    for (auto& s : strs) {
      if (s.size() < 4) {
        char c2 = s[0];
        int r2 = s[1] - '0';
        if (s.size() == 3) {
          r2 = r2 * 10 + (s[2] - '0');
        }
        const int depend_idx = getIdx(r2, c2);
        depend_cells[depend_idx]++;
        affect[depend_idx].insert(idx);
        new_val += idx_to_val[depend_idx];
      } else {
        int r2, r3;
        char c2, c3;
        getRectFromStr(s, r2, c2, r3, c3);
        for (int i = r2; i <= r3; i++) {
          for (char j = c2; j <= c3; j++) {
            const int depend_idx = getIdx(i, j);
            depend_cells[depend_idx]++;
            affect[depend_idx].insert(idx);
            new_val += idx_to_val[depend_idx];
          }
        }
      }
    }

    // Not `set` since it will call `clearDependCells`.
    //set(r, c, new_val);
    updateCell(idx, new_val);
    return new_val;
  }

 private:
  const int kShift = 5;
  inline int getRow(int idx) { return idx >> kShift; }
  inline char getCol(int idx) {
    // cout << "getCol: " <<
    // Not: return (idx & ((1 << kShift) - 1) + 'A');
    return (idx & ((1 << kShift) - 1)) + 'A';
  }
  inline int getIdx(int r, char c) {
    // brace is essential here.
    return (r << kShift) + (c - 'A');
  }
  // inline int getIdx(int r, int c) { return (r << kShift) + c; }
  void getRectFromStr(const string& s, int& r1, char& c1, int& r2, char& c2) {
    c1 = s[0];
    r1 = s[1] - '0';
    int i = 2;
    if (s[i] != ':') {
      r1 = r1 * 10 + (s[i] - '0');
      i++;
    }
    i++;
    c2 = s[i];
    r2 = s[i + 1] - '0';
    if (i + 2 < s.size()) {
      r2 = r2 * 10 + (s[i + 2] - '0');
    }
  }
  int width;
  int height;
  unordered_map<int, int> idx_to_val;
  unordered_map<int, unordered_set<int> > affect;
  unordered_map<int, unordered_map<int, int> > sum_cell_and_times;
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(H, W);
 * obj.set(r,c,v);
 * int param_2 = obj.get(r,c);
 * int param_3 = obj.sum(r,c,strs);
 */

int main(int argc, char* argv[]) {
  Excel excel(3, 'C');
  // vector<string> s{"A2"};
  excel.sum(1, 'A', {"A2"});
  excel.set(2, 'A', 1);
  cout << excel.get(1, 'A') << endl;

  /* `set` should call `clearDependCells`, otherwise failed on:
   Input: ["Excel","set","sum","set","get","set","get"]
   [[5,"E"],[1,"A",1],[2,"B",["A1"]],[2,"B",0],[2,"B"],[1,"A",5],[2,"B"]]
   Output
   [null,null,1,null,0,null,4]
   Expected
   [null,null,1,null,0,null,0]
   */
  return 0;
}
