#include <vector>
#include <iostream>  

#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

class CheckArea {
 public:
  static bool isInArea(const vector<Vector2d>& polygon, const Vector2d& p);
};

bool CheckArea::isInArea(const vector<Vector2d>& polygon, const Vector2d& p) {
  bool sign;
  for (int i = 0; i < polygon.size(); ++i) {
    int j = i + 1;
    if (j >= polygon.size()) {
      j = 0;
    }
    const Vector2d v1 = p - polygon[i];
    const Vector2d v2 = polygon[j] - polygon[i];
    Vector3d va(v1.x(), v1.y(), 0);
    Vector3d vb(v2.x(), v2.y(), 0);
    Vector3d vc = va.cross(vb);
    if (vc.z() == 0) {
      return false;
    }
    if (i == 0) {
      sign = vc.z() > 0;
    } else {
      if (sign && vc.z() < 0) {
        return false;
      } else if (!sign && vc.z() > 0) {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  vector<Vector2d> triangle{{0, 0}, {1, 0}, {0.5, 1}};
  Vector2d p(0.5, 0.5);
  cout << "is in triangle: " << CheckArea::isInArea(triangle, p) << endl;
  return 0;
}
