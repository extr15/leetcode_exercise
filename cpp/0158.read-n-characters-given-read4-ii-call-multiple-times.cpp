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
      int idx = 0;
      while(!q.empty() && n>0) {
        buf[idx++] = q.front();
        q.pop();
        n--;
      }
      buf += idx;
      int total_cnt = idx;
      while(n>0) {
        int cnt = read4(buf);
        if(n >= cnt) {
          buf += cnt;
          total_cnt += cnt;
        }
        else {
          total_cnt += n;
          for(int i=n;i<cnt;i++) {
            q.push(buf[i]);
          }
          break;
        }
        n -=cnt;
        if(cnt < 4) {
          break;
        }
      }
      return total_cnt;
    }
private:
    queue<char> q;
};
