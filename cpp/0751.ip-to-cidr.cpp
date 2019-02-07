#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
//#define Debug(x) x
#define Debug(x) 
 public:
  string ipIntToString(unsigned int ip_int) {
    string ip;
    for (int i = 0; i < 4; i++) {
      int shift = 8 * (3 - i);
      ip += std::to_string((ip_int >> shift) & 0xff);
      if (i < 3) {
        ip += ".";
      }
    }
    return ip;
  }
  int getLastOne(unsigned int ip_int) {
    int sign = (int)ip_int;
    return (sign & (-sign));

//    int val = 1;
//    for(int i=0; i<32; i++) {
//      if((ip_int & val) != 0) {
//        break;
//      }
//      val = (val << 1);
//    }
//    return val;
  }
  vector<string> ipToCIDR(string ip, int n) {
    unsigned int ip_int = 0;
    {
      std::istringstream iss(ip);
      for (int i = 0; i < 4; i++) {
        int tmp;
        iss >> tmp;
        Debug(cout << "tmp: " << tmp << endl);
        ip_int = (ip_int << 8) + tmp;
        if(iss.peek() == '.') {
          iss.ignore();
        }
      }
    }
    vector<string> res;
    int k = 0;
    Debug(cout << "ip_int: " << ip_int << endl);
    //int last_one_bit = (ip_int & (-ip_int));
    int last_one_bit = getLastOne(ip_int);
    while (k < n) {
      Debug(cout << "k: " <<k << ", last_one_bit: " << last_one_bit << endl);
      if (k + last_one_bit <= n) {
        k += last_one_bit;
        string cur = ipIntToString(ip_int);
        ip_int += last_one_bit;
        int shift_cnt = 0;
        while(last_one_bit != 1) {
          shift_cnt++;
          last_one_bit = (last_one_bit >> 1);
        }
        Debug(cout << "cur: " << cur << ", shift_cnt: " << shift_cnt << endl);
        cur += "/" + std::to_string(32-shift_cnt);
        res.push_back(cur);
        //last_one_bit = (ip_int & (-ip_int));
        last_one_bit = getLastOne(ip_int);
      }
      else {
        last_one_bit = last_one_bit>>1;
      }
    }
    return res;
  }
};

int main(int argc, char *argv[]) { 
  Solution sol;
  string ip("255.0.0.7");
  //string ip("10.0.0.7");
  int n = 10;
  auto res = sol.ipToCIDR(ip, n);
  for(int i=0; i<res.size(); i++) {
    cout << res[i] << endl;
  }
  return 0; 
}
