#ifndef FIGURES
#define FIGURES
#include<vector>

class Point {
 private:
  float x, y;
 public:
  Point() {
    x = 0;
    y = 0;
  }
  Point(float new_x, float new_y ) {
    x = new_x;
    y = new_y;
  }
  Point &operator=(const Point &other) {
    // Guard self assignment
    if (this == &other)
      return *this;
    this->x = other.x;
    this->y = other.y;
    return *this;
  }
  float X() {
    return x;
  }
  float Y() {
    return y;
  }
  void set_x(float new_x) {
    x = new_x;
  }
  void set_y(float new_y) {
    y = new_y;
  }
  float radius_vector_length();
};

class Segment {
 public:
  Point a, b;
  Segment(Point new_a, Point new_b) {
    a = new_a;
    b = new_b;
  }
  float get_length();
  bool is_intersection(Segment &other_segment);
  bool is_point_on_segment(Point &p);
};

class Polygon {
 public:
  std::vector<Point> points;
  Polygon() {

  }
  Polygon(std::vector<float> &x, std::vector<float> &y) {
    for (int i = 0; i < x.size(); ++i) {
      points.push_back(Point(x[i], y[i]));
    }
  }
  bool is_point_in_polygon(Point &p);
  bool is_intersection(Polygon &other_polygon);
};

class Rectangle: public Polygon {
 public:
  Rectangle(float x1, float y1, float x2, float y2) {
    points.push_back(Point(x1, y1));
    points.push_back(Point(x2, y1));
    points.push_back(Point(x2, y2));
    points.push_back(Point(x1, y2));
  }
};

class Circle {
 private:
  float r;
  Point c;
 public:
  Circle() {
    r = 0.0;
  }
  Circle(float rad, float x, float y) {
    r = rad;
    c.set_x(x);
    c.set_y(y);
  }
  bool is_intersection(Circle &other_circle);
  bool is_intersection(Polygon &other_polygon);
};

Point ProectionPOnSegment(Point &p, Segment &s);
float dot_product(Point &e1, Point &e2);

#endif // FIGURES
