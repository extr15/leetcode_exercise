class SnakeGame {
 public:
  typedef pair<int, int> Coord;
  /** Initialize your data structure here.
      @param width - screen width
      @param height - screen height
      @param food - A list of food positions
      E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0].
   */
  SnakeGame(int width, int height, vector<pair<int, int>> food)
      : board_width_(width), board_height_(height), food_(food), food_idx_(0) {
    snake_.push_back({0, 0});
  }

  /** Moves the snake.
      @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
      @return The game's score after the move. Return -1 if game over.
      Game over when snake crosses the screen boundary or bites its body. */
  int move(string direction) {
    const int n = snake_.size();
    const Coord& cur_head = snake_[n - 1];
    Coord next_head = cur_head;
    if (direction == "U") {
      next_head.first--;
    } else if (direction == "D") {
      next_head.first++;
    } else if (direction == "L") {
      next_head.second--;
    } else if (direction == "R") {
      next_head.second++;
    }
    if (next_head.first < 0 || next_head.first >= board_height_ || next_head.second < 0 ||
        next_head.second >= board_width_) {
      return -1;
    }
    if (food_idx_ < food_.size() && next_head == food_[food_idx_]) {
      food_idx_++;
      snake_.push_back(next_head);
    } else {
      for (int i = 0; i < n - 1; i++) {
        if(snake_[i+1] == next_head) {
          return -1;
        }
        snake_[i] = snake_[i + 1];
      }
      snake_[n - 1] = next_head;
    }
    return food_idx_;
  }

 private:
  vector<Coord> snake_;
  vector<Coord> food_;
  int food_idx_;
  int board_width_;
  int board_height_;
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */
