#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  if(argc == 2) {
    fstream myfile(argv[1]);
    if (myfile.is_open()) { //проверка открытия файла
      float xn, yx;
      myfile >> xn;
      myfile >> yx;
      float temp_coord;
      vector<float> coord_x; // координаты точек
      vector<float> coord_y;
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
      cout << "Leftmost: " << coord_x[left] << " " << coord_y[left] << endl;
      cout << "Rightmost: " << coord_x[right] << " " << coord_y[right] << endl;
    } 
  } 
  return 0;
}
