// Forward declaration of ArrayReader class.
class ArrayReader;

class Solution {
 public:
  const static int kIntMax = 2147483647;

  int search(const ArrayReader& reader, int target) {
    if (target >= 10000) {
      return -1;
    }
    int lo = 0, hi = kIntMax;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      int v = reader.get(mid);
      if (v == target) {
        return mid;
      }
      if (v == kIntMax || v > target) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    return -1;
  }
};
