// AC. slow.
class Solution {
 public:
  vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
    const int n = pid.size();
    vector<int> res;
    bool find_kill = false;
    for (int i = 0; i < n; i++) {
      if (pid[i] == kill) {
        find_kill = true;
        break;
      }
      if (ppid[i] == kill) {
        find_kill = true;
        break;
      }
    }
    if (!find_kill) {
      return res;
    }
    unordered_set<int> visited;
    queue<int> q;
    q.push(kill);
    visited.insert(kill);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      res.push_back(cur);
      for (int i = 0; i < n; i++) {
        int next = pid[i];
        int pp = ppid[i];
        if (pp == cur && visited.find(next) == visited.end()) {
          visited.insert(next);
          q.push(next);
        }
      }
    }
    return res;
  }
};

// AC. slow.
class Solution {
 public:
  vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
    const int n = pid.size();
    vector<int> res;
    bool find_kill = false;
    int kill_idx;
    for (int i = 0; i < n; i++) {
      if (pid[i] == kill) {
        find_kill = true;
        kill_idx = i;
        break;
      }
    }

    queue<int> q;
    q.push(kill);
    vector<bool> visited(n, false);
    visited[kill_idx] = true;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      res.push_back(cur);
      for (int i = 0; i < n; i++) {
        int next = pid[i];
        int pp = ppid[i];
        if (pp == cur && visited[i] == false) {
          visited[i] = true;
          q.push(next);
        }
      }
    }
    return res;
  }
};

// AC. fast.
class Solution {
 public:
  vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
    const int n = pid.size();
    vector<int> res;
    bool find_kill = false;
    int kill_idx;
    unordered_map<int, vector<int>> ppid_to_pid_idx;
    for (int i = 0; i < n; i++) {
      if (pid[i] == kill) {
        find_kill = true;
        kill_idx = i;
      }
      ppid_to_pid_idx[ppid[i]].push_back(i);
    }

    queue<int> q;
    q.push(kill);
    vector<bool> visited(n, false);
    visited[kill_idx] = true;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      res.push_back(cur);
      for (auto pid_idx : ppid_to_pid_idx[cur]) {
        if (!visited[pid_idx]) {
          q.push(pid[pid_idx]);
        }
      }
    }
    return res;
  }
};
