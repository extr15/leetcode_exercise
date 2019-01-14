class StringIterator {
 public:
  StringIterator(string compressedString) : str(compressedString) {
    ch_idx = 0;
    ch_cnt = 0;
    ch_total_cnt = 0;
  }

  char next() {
    if (ch_idx >= str.size()) {
      return ' ';
    }
    char ch = str[ch_idx];
    if (ch_total_cnt == 0) {
      ch_total_cnt = getChTotalCnt(ch_idx, ch_total_cnt_bit);
    }
    ch_cnt++;
    if (ch_cnt >= ch_total_cnt) {
      ch_idx += ch_total_cnt_bit + 1;
      ch_cnt = 0;
      ch_total_cnt = 0;
    }
    return ch;
  }

  bool hasNext() {
    if (ch_idx >= str.size()) {
      return false;
    } else {
      return true;
    }
  }

 private:
  int getChTotalCnt(int idx, int& bit) {
    idx++;
    int val = 0;
    bit = 0;
    while (idx < str.size() && str[idx] >= '0' && str[idx] <= '9') {
      val = val * 10 + (str[idx] - '0');
      idx++;
      bit++;
    }
    return val;
  }
  int ch_idx;
  int ch_cnt;
  int ch_total_cnt;
  int ch_total_cnt_bit;
  string str;
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator obj = new StringIterator(compressedString);
 * char param_1 = obj.next();
 * bool param_2 = obj.hasNext();
 */
