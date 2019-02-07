// AC.
class Solution {
 public:
  bool isPowerOfThree(int n) {
    // don't forget `0`.
    if (n == 0) {
      return false;
    }

    while (n % 3 == 0) {
      n /= 3;
    }
    return (n == 1);
  }
};

// AC.
class Solution {
 public:
  bool isPowerOfThree(int n) {
    if (n == 0) {
      return false;
    }
    double r = log(n) / log(3);
    if (std::abs(r - std::round(r)) < 1e-10) {
      return true;
    } else {
      return false;
    }
  }
};
