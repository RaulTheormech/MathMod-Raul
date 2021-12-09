#include "figures.h"
#include <math.h>

float Point::radius_vector_length() {
  return std::sqrt(x * x + y * y);
}

float Segment::get_length() {
  Point radius_vector(a.X() - b.X(), a.Y() - b.Y());
  return radius_vector.radius_vector_length();
}

bool Segment::is_intersection(Segment &other_segment) {
  float a1, b1, c1;
  a1 = this->b.Y() - this->a.Y();
  b1 = this->a.X() - this->b.X();
  c1 = this->b.X() * this->a.Y() - this->a.X() * this->b.Y();

  float a2, b2, c2;
  a2 = other_segment.b.Y() - other_segment.a.Y();
  b2 = other_segment.a.X() - other_segment.b.X();
  c2 = other_segment.b.X() * other_segment.a.Y()
       - other_segment.a.X() *  other_segment.b.Y();
  float det = a2 * b1 - b2 * a1;
  Point intP; // точка пересечения
  if (det != 0) { // не коллинеартны
    if (b1 == 0) {
      intP.set_x(-c1 / a1);
      intP.set_y((a2 * c1 / a1 - c2) / b2);
    } else {
      intP.set_x((b2 * c1 - c2 * b1) / det);
      intP.set_y(-(c1 + a1 * intP.X()) / b1);
    }
    // Точка пересечения должна лежать на обоих отрезках
    // Если AB = AP + PB, то P лежит на отрезке линии AB.
    if (this->is_point_on_segment(intP)
        && other_segment.is_point_on_segment(intP)) {
      return true;
    }
  }
  return false;
}

bool Segment::is_point_on_segment(Point &p) {
  Segment AP(this->a, p);
  Segment PB(p, this->b);

  if (this->get_length() != AP.get_length() + PB.get_length()) {
    return false;
  }
  return true;
}

bool Circle::is_intersection(Circle &other_circle) {
  Segment between_centers(this->c, other_circle.c);
  if (between_centers.get_length() > this->r + other_circle.r) {
    return false;
  }
  return true;
}

bool Circle::is_intersection(Polygon &other_polygon) {
  if (other_polygon.is_point_in_polygon(this->c)) {
    return true;
  }
  for (int i = 0; i < other_polygon.points.size(); i++) {
    int j = (i + 1) %
            other_polygon.points.size(); // следующая точка в полигоне
    Segment oa(this->c, other_polygon.points[i]);
    Segment ob(this->c, other_polygon.points[j]);
    if (oa.get_length() < this->r || ob.get_length() < this->r) {
      return true;
    }
    Segment ab(other_polygon.points[j], other_polygon.points[j]);
    Point proj_o = ProectionPOnSegment(this->c, ab);
    Point distance_c_to_proj(proj_o.X() - this->c.X(),
                             proj_o.Y() - this->c.Y());
    if (ab.is_point_on_segment(proj_o)
        && distance_c_to_proj.radius_vector_length() < this->r ) {
      return true;
    }
  }
  return false;
}


Point ProectionPOnSegment(Point &p, Segment &s) {
  // проектирование точки p на отрезок S
  Point e1(s.b.X() - s.a.X(), s.b.Y() - s.a.Y());
  Point e2(p.X() - s.a.X(), p.Y() - s.a.Y());
  double val = dot_product(e1, e2);
  double e1_len = e1.radius_vector_length();
  double e2_len = e2.radius_vector_length();

  if (e2_len == 0) {
    return p;
  }
  double recArea = dot_product(e1, e1);
  double koef = val / recArea;
  Point proj(s.a.X() + koef * e1.X(), s.a.Y() + koef * e1.Y());
  return proj;
}

float dot_product(Point &e1, Point &e2) {
  return e1.X() * e2.X() + e1.Y() * e2.Y();
}

bool Polygon::is_point_in_polygon(Point &p) {
  int intersection_count = 0;
  Segment op(p, Point(0, 0));
  for (int i = 0; i < this->points.size(); i++) {
    int j = (i + 1) %
            this->points.size(); // следующая точка в полигоне
    Segment ab(this->points[i], this->points[j]);
    if (ab.is_intersection(op)) {
      intersection_count++;
    }
  }
  if (intersection_count % 2 == 1) {
    return true;
  }
  return false;
}

bool Polygon::is_intersection(Polygon &other_polygon) {
  for (int i = 0; i < other_polygon.points.size(); i++) {
    if (this->is_point_in_polygon(other_polygon.points[i])) {
      return true;
    }
  }
  for (int i = 0; i < this->points.size(); i++) {
    if (other_polygon.is_point_in_polygon(this->points[i])) {
      return true;
    }
  }
  return false;
}
