#include <iostream>
#include "file_reader.cpp"
using namespace std;

int main() {
  std::vector<Rectangle> rects;
  std::vector<Circle> circles;
  std::vector<Polygon> polygons;
  read_from_file("input.txt", &rects, &circles, &polygons);
  std::cout << "Rects count = " << rects.size() << std::endl;
  std::cout << "Circles count = " << circles.size() << std::endl;
  std::cout << "Polygons count = " << polygons.size() << std::endl;

  /// Проверка пересечений кругов
  for (int i = 0; i < circles.size(); i++) {
    /// с кругами
    for (int j = i + 1; j < circles.size(); j++) {
      if (circles[i].is_intersection(circles[j])) {
        std::cout << "(Circle " << i << "; Circle " << j << ")" << std::endl;
      }
    }
    /// с прямоугольниками
    for (int j = 0; j < rects.size(); j++) {
      if (circles[i].is_intersection(rects[j])) {
        std::cout << "(Circle " << i << "; Rectangle " << j << ")" << std::endl;
      }
    }
    /// с полигонами
    for (int j = 0; j < polygons.size(); j++) {
      if (circles[i].is_intersection(polygons[j])) {
        std::cout << "(Circle " << i << "; Polygon " << j << ")" << std::endl;
      }
    }
  }

  /// Проверка пересечений прямоугольников
  for (int i = 0; i < rects.size(); i++) {
    /// с кругами
    for (int j = i + 1; j < rects.size(); j++) {
      if (rects[i].is_intersection(rects[j])) {
        std::cout << "(Rectangle " << i << "; Rectangle " << j << ")" << std::endl;
      }
    }
    /// с полигонами
    for (int j = 0; j < polygons.size(); j++) {
      if (rects[i].is_intersection(polygons[j])) {
        std::cout << "(Rectangle " << i << "; Polygon " << j << ")" << std::endl;
      }
    }
  }

  /// Проверка пересечений полигонов
  for (int i = 0; i < polygons.size(); i++) {
    /// с полигонами
    for (int j = i + 1; j < polygons.size(); j++) {
      if (polygons[i].is_intersection(polygons[j])) {
        std::cout << "(Polygon " << i << "; Polygon " << j << ")" << std::endl;
      }
    }
  }


}
