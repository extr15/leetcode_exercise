#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Codec {
 public:
  // Encodes a list of strings to a single string.
  string encode(vector<string>& strs) {
    string res;
    for (int i = 0; i < strs.size(); i++) {
      res += std::to_string(strs[i].size());
      res += "#";
      res += strs[i];
    }
    return res;
  }

  // Decodes a single string to a list of strings.
  vector<string> decode(string s) {
    const int n = s.size();
    int i = 0;
    vector<string> res;
    while (i < n) {
      int len = 0;
      while (i < n && s[i] != '#') {
        len = len * 10 + (s[i] - '0');
        i++;
      }
      i++;
      //cout << "len: " << len << " " << i << endl;
      string str = s.substr(i, len);
      //cout << "str: " << str << endl;
      res.push_back(str);
      i += len;
    }
    return res;
  }
};

int main(int argc, char* argv[]) {
  Codec codec;
  vector<string> src;
  src.push_back("0");
  string res = codec.encode(src);
  cout << "res: " << res << endl;
  vector<string> dst = codec.decode(res);
  cout << "dst" << endl;
  for (auto s : dst) {
    cout << s << " ";
  }
  cout << endl;

  return 0;
}
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
