#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const float g = 9.81;

int traectories(float x_0, float h_0, float vx0, float vy0,
                int start_idx,
                const std::vector<float> &coord_x,
                const std::vector<float> &coord_y) {
  if (vx0 > 0) {
    int new_idx = start_idx + 1;
    float xi = coord_x[new_idx];
    float ti = (xi - x_0) / vx0;
    float hi = -0.5 * g * ti * ti + vy0 * ti + h_0;

    if (hi <= 0) {
      return start_idx;
    } else if (coord_y[new_idx] >= hi) {
      float vxi = -vx0;
      float vyi = -g * ti + vy0;
      return traectories(xi, hi, vxi, vyi, new_idx, coord_x, coord_y);
    } else {
      if (new_idx >= coord_x.size() - 1) {
        return new_idx;
      }
      float vxi = vx0;
      float vyi = -g * ti + vy0;
      return traectories(xi, hi, vxi, vyi, new_idx, coord_x, coord_y);
    }
  }

  if (vx0 <= 0) {
    int new_idx = start_idx - 1;
    float xi = coord_x[new_idx];
    float ti = (xi - x_0) / vx0;
    float hi = -0.5 * g * ti * ti + vy0 * ti + h_0;

    if (hi <= 0) {
      return new_idx;
    } else if (coord_y[new_idx] > hi) {
      float vxi = -vx0;
      float vyi = -g * ti + vy0;
      return traectories(xi, hi, vxi, vyi, new_idx, coord_x, coord_y);
    } else {
      float vxi = vx0;
      float vyi = -g * ti + vy0;
      return traectories(xi, hi, vxi, vyi, new_idx, coord_x, coord_y);
    }
  }
  return start_idx;
}

int main(int argc, char **argv) {
  if(argc == 2) {
    // есть один агрумент
    // в argv[1] содержится строка с первым агрументом (имя файла)
//    std::cout << "input filename: " << argv[1] << std::endl;
    string line;
    fstream myfile(argv[1]);
    if (myfile.is_open()) { //проверка открытия файла
      float h0, dy, dx;
      myfile >> h0;  // считываем начальные данные
      myfile >> dx;
      myfile >> dy;
      int i = 0;
      float temp_coord;
      std::vector<float> coord_x; // координаты перегородок
      std::vector<float> coord_y;
      coord_x.push_back(0);
      coord_y.push_back(h0);
      while (myfile >> temp_coord) {
        if (i % 2 == 0) {
          coord_x.push_back(temp_coord);
        } else {
          coord_y.push_back(temp_coord);
        }
        ++i;
      }
      myfile.close();

      //int idx = traectories(0, h0, dx, dy, 0, coord_x, coord_y);
      //std::cout << idx;

      // переходим к расчету
      float hi = h0;
      float ti = 0;
      bool is_find = false;
      for (int i = 0; i < coord_x.size(); ++i) {
        ti = coord_x[i] / dx;
        hi = -0.5 * g * ti * ti + dy * ti + h0;
        if (hi < coord_y[i] || hi <= 0) {
//          std::cout << "mat. the point will land on the site " << i - 1 << std::endl;
          std::cout << i - 1 << std::endl;
          is_find = true;
          break;
        }
      }
      if (is_find != true) {
        if (coord_x.size() - 1 == 0) {
          return 1;
        }
        std::cout << coord_x.size() - 1 << std::endl;
      } 

    } else {
      std::cout << "Unable to open file" << std::endl;
    }
  } else {
    std::cout << "there are no arguments or there are more of them than we expect"
              << std::endl;
  }
  return 0;
}
