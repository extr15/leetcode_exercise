// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
 public:
  /**
   * @param buf Destination buffer
   * @param n   Maximum number of characters to read
   * @return    The number of characters read
   */
  int read(char *buf, int n) {
    int total_cnt = 0;
    while (n > 0) {
      int cnt = read4(buf);
      if (n > cnt) {
        total_cnt += cnt;
        buf += cnt;
      } else {
        total_cnt += n;
        break;
      }
      n -= cnt;
      if (cnt < 4) {
        break;
      }
    }
    return total_cnt;
  }
};
