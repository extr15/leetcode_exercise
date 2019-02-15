
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& a) {
      const int n = a.size();
      sort(a.begin(), a.end());
      for(int i=n-1;i>=2;i--) {
        if(a[i-2] + a[i-1] > a[i]) {
          int perimeter = a[i] + a[i-2] + a[i-1];
          return perimeter;
        }
      }
      return 0;
        
    }
};

int main(int argc, char *argv[]) {
  
    return 0;
}
