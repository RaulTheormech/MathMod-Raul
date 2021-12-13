#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  const float g = 9.81;
  if(argc == 2) {
    // есть один агрумент
    // в argv[1] содержится строка с первым агрументом (имя файла)
    //std::cout << "input filename: " << argv[1] << std::endl;
    string line;
    fstream myfile(argv[1]);
    if (myfile.is_open()) { //проверка открытия файла
      float h0, dy, dx;
      myfile >> h0;  // считываем начальные данные
      myfile >> dx;
      myfile >> dy;
      int i = 0;
      float temp_coord;
      vector<float> coord_x; // координаты перегородок
      vector<float> coord_y;
      while (myfile >> temp_coord) {
        if (i % 2 == 0) {
          coord_x.push_back(temp_coord);
        } else {
          coord_y.push_back(temp_coord);
        }
        ++i;
      }
      myfile.close();

      // переходим к расчету
      float hi = h0;
      float ti = 0;
      bool is_find = false;
      for (int i = 0; i < coord_x.size(); ++i) {
        ti = coord_x[i] / dx;
        hi = -0.5 * g * ti * ti + dy * ti + h0;
        if (hi < coord_y[i] || hi <= 0) {
          cout << i << endl;
          is_find = true;
          break;
        }
      }
      if (is_find != true) {
        cout << coord_x.size()
                  << std::endl;
      }

    } 
  } 
  return 0;
}
