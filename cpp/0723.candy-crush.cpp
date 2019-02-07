#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  typedef pair<int, int> Coord;
  void printBoard(const vector<vector<int>>& board) {
    cout << "board" << endl;
    const int m = board.size();
    const int n = board[0].size();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cout << board[i][j] << " ";
      }
      cout << endl;
    }
  }
  void findConsecutiveThreeSame(const vector<vector<int>>& board, vector<Coord>& crush) {
    const int m = board.size();
    const int n = board[0].size();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n - 2; j++) {
        if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
          crush.push_back({i, j});
          crush.push_back({i, j + 1});
          crush.push_back({i, j + 2});
          j += 2;
          while (j < n - 1 && board[i][j] == board[i][j + 1]) {
            crush.push_back({i, j + 1});
            j++;
          }
        }
      }
    }
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < m - 2; i++) {
        if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
          crush.push_back({i, j});
          crush.push_back({i + 1, j});
          crush.push_back({i + 2, j});
          i += 2;
          while (i < m - 1 && board[i][j] == board[i + 1][j]) {
            crush.push_back({i + 1, j});
            i++;
          }
        }
      }
    }
  }
  vector<vector<int>> candyCrush(vector<vector<int>>& board) {
    const int m = board.size();
    const int n = board[0].size();
    while (true) {
      vector<Coord> crush;
      findConsecutiveThreeSame(board, crush);
      if (crush.empty()) {
        break;
      }
      //cout << "crush" << endl;
      for (auto& c : crush) {
        //cout << "c: " << c.first << " " << c.second << endl;
        board[c.first][c.second] = 0;
      }
      //printBoard(board);
      for (int j = 0; j < n; j++) {
        int idx = m - 1;
        for (int i = m - 1; i >= 0; i--) {
          if (board[i][j] != 0) {
            //cout << i << " " << j << " " << idx << " " << board[i][j] << endl;
            board[idx][j] = board[i][j];
            if(i != idx) {
              board[i][j] = 0;
            }
            idx--;
          }
        }
      }
      //printBoard(board);
    }
    return board;
  }
};

int main(int argc, char* argv[]) {
  vector<vector<int>> board{{110, 5, 112, 113, 114}, {210, 211, 5, 213, 214},
                            {310, 311, 3, 313, 314}, {410, 411, 412, 5, 414},
                            {5, 1, 512, 3, 3},       {610, 4, 1, 613, 614},
                            {710, 1, 2, 713, 714},   {810, 1, 2, 1, 1},
                            {1, 1, 2, 2, 2},         {4, 1, 4, 4, 1014}};
  Solution sol;
  sol.candyCrush(board);

  return 0;
}
