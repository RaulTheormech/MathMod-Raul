#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int main(int argc, char **argv) {
  fstream myfile("in.txt");
  if (myfile.is_open()) { //проверка открытия файла
    float xn, yx;
    myfile >> xn;
    myfile >> yx;
    float temp_coord;
    std::vector<float> coord_x; // координаты точек
    std::vector<float> coord_y;
    while (myfile >> temp_coord) {
      coord_x.push_back(temp_coord);
      myfile >> temp_coord;
      coord_y.push_back(temp_coord);
    }
    myfile.close();

    // вариант 1
    int left = 0, right = 0;
    float min_left_cos = 1, min_right_cos = 1;
    float len_v = std::sqrt(xn * xn + yx * yx);
    float cos_alpha = xn / len_v, sin_alpha = yx / len_v;

    for (int i = 0; i < coord_x.size(); ++i) {
      float new_x = cos_alpha * coord_x[i] + sin_alpha * coord_y[i];
      float new_y = -sin_alpha * coord_x[i] + cos_alpha * coord_y[i];

      float prod_dot = new_x * 1 + new_y * 0;
      float len_p = std::sqrt(new_x * new_x + new_y * new_y);
      float cos = prod_dot / 1 / len_p;
      if (new_y > 0) { //слева
        if (cos < min_left_cos) {
          min_left_cos = cos;
          left = i;
        }
      }
      if (new_y <= 0) { // справа
        if (cos < min_right_cos) {
          min_right_cos = cos;
          right = i;
        }
      }
    }
    std::cout << "Leftmost: " << coord_x[left] << " " << coord_y[left] << std::endl;
    std::cout << "Rightmost: " << coord_x[right] << " " << coord_y[right] <<
              std::endl;

//      // вариант 2
//      float max_left = 0, max_right = 0;
//      for (int i = 0; i < coord_x.size(); ++i) {
//        float new_x = cos_alpha * coord_x[i] + sin_alpha * coord_y[i];
//        float new_y = -sin_alpha * coord_x[i] + cos_alpha * coord_y[i];

//        if (new_y > max_left) {
//          max_left = new_y;
//          left = i;
//        }
//        if (new_y < max_right) {
//          max_right = new_y;
//          right = i;
//        }
//      }
//      std::cout << "Case 2" << std::endl;
//      std::cout << "Leftmost: " << coord_x[left] << " " << coord_y[left] << std::endl;
//      std::cout << "Rightmost: " << coord_x[right] << " " << coord_y[right] <<
//                std::endl;
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
  return 0;
}
