#include <iostream>

using namespace std;

class Point {
private:
  double x, y;

public:
  Point() { x = y = 0; }
  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double getx() const { return x; }
  double gety() const { return y; }
  Point &operator+=(const Point &p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  friend ostream &operator<<(ostream &out, const Point &p);
};

ostream &operator<<(ostream &out, const Point &p) {
  out << "(" << p.x << "," << p.y << ")";
  return out;
}

Point operator+(const Point &p1, const Point &p2) {
  Point p3(p1.getx() + p2.getx(), p1.gety() + p2.gety());
  return p3;
}

int main(void) {
  Point p1(2.3, 4.4);
  Point p2(2.3, 4.4);
  p1 += p2;
  Point p3 = p1 + p2;

  cout << p1 << endl;
  cout << p2 << endl;
  cout << p3 << endl;
  return 0;
}
