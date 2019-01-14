class FileSystem {
 public:
  FileSystem() { root = new File("/", true); }

  vector<string> ls(string path) {
    File* cur = root;
    int i = 0;
    const int n = path.size();
    bool new_dir = false;
    string dir_name;
    vector<string> res;
    File* parent = root;
    while (i < n) {
      const char ch = path[i];
      if (new_dir) {
        if (ch != '/') {
          dir_name += ch;
        }
        if (ch == '/' || i == n - 1) {
          auto& cur_dir = cur->children;
          if (cur_dir.find(dir_name) == cur_dir.end()) {
            return res;
          } else {
            parent = cur;
            cur = cur_dir[dir_name];
            dir_name = "";
          }
        }
      } else if (path[i] == '/') {
        new_dir = true;
      }
      i++;
    }
    if (cur->is_dir == false) {
      res.push_back(cur->name);
      return res;
    }
    if (cur->children.empty()) {
      return res;
    } else {
      for (auto& c : cur->children) {
        res.emplace_back(c.first);
      }
      sort(res.begin(), res.end());
      return res;
    }
  }

  void mkdir(string path) {
    int i = 0;
    string dir_name;
    File* cur = root;
    while (getNextName(path, i, dir_name)) {
      auto& cur_dir = cur->children;
      if (cur_dir.find(dir_name) != cur_dir.end()) {
        cur = cur_dir[dir_name];
      } else {
        File* child = new File(dir_name, true);
        cur_dir.insert({dir_name, child});
        cur = child;
      }
    }
  }

  void addContentToFile(string filePath, string content) {
    int i = 0;
    string dir_name;
    File* cur = root;
    while (getNextName(filePath, i, dir_name)) {
      if (i != filePath.size()) {
        cur = cur->children[dir_name];
      } else {
        auto& cur_dir = cur->children;
        if (cur_dir.find(dir_name) != cur_dir.end()) {
          cur = cur_dir[dir_name];
          cur->content += content;
        } else {
          File* new_file = new File(dir_name, false, content);
          cur_dir.insert({dir_name, new_file});
        }
      }
    }
  }

  string readContentFromFile(string filePath) {
    int i = 0;
    string dir_name;
    File* cur = root;
    while (getNextName(filePath, i, dir_name)) {
      if (i != filePath.size()) {
        cur = cur->children[dir_name];
      } else {
        auto& cur_dir = cur->children;
        if (cur_dir.find(dir_name) != cur_dir.end()) {
          return cur_dir[dir_name]->content;
        } else {
          return "";
        }
      }
    }
  }

 private:
  struct File {
    File(string _name, bool _dir, string _content = "")
        : name(_name), is_dir(_dir), content(_content){};
    string name;
    bool is_dir;
    string content;
    unordered_map<string, File*> children;
  };
  bool getNextName(const string s, int& i, string& dir_name) {
    const int n = s.size();
    if (i >= n) {
      return false;
    }
    bool new_dir = false;
    dir_name = "";
    // skip the leading '/'.
    while (i < n && s[i] == '/') {
      i++;
    }
    while (i < n) {
      const char ch = s[i];
      if (ch != '/') {
        dir_name += ch;
      }
      if (ch == '/' || i == n - 1) {
        i++;
        return true;
      }
      i++;
    }
    return false;
  }

  File* root;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */

[
  "FileSystem", "mkdir", "ls", "ls", "mkdir", "ls", "ls", "addContentToFile", "ls", "ls", "ls"
][[], ["/goowmfn"], ["/goowmfn"], ["/"], ["/z"], ["/"], ["/"], [ "/goowmfn/c", "shetopcy" ], ["/z"],
  ["/goowmfn/c"], ["/goowmfn"]]
 [null, null, [], ["goowmfn"], null, [ "goowmfn", "z" ], [ "goowmfn", "z" ], null, [], ["c"], ["c"]]

