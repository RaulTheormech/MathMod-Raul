#include <fstream>
#include <iostream>
#include <string>
#include "figures.h"

bool is_float(const std::string &s) {
  try {
    std::stof(s);
  } catch(...) {
    return false;
  }
  return true;
}

void read_from_file(std::string filename,
                    std::vector<Rectangle> *rects,
                    std::vector<Circle> *circles,
                    std::vector<Polygon> *polygons) {
  std::cout << "input filename: " << filename << std::endl;
  std::string line;
  std::fstream myfile(filename);
  if (myfile.is_open()) { //проверка открытия файла
    myfile >> line;
    do {
      if (line == "RECTAGNLE") {
        float x1, y1, x2, y2;
        myfile >> x1;
        myfile >> y1;
        myfile >> x2;
        myfile >> y2;
        rects->push_back(Rectangle(x1, y1, x2, y2));
        myfile >> line;
      } else if (line == "CIRCLE") {
        float rad, x, y;
        myfile >> rad;
        myfile >> x;
        myfile >> y;
        circles->push_back(Circle(rad, x, y));
        myfile >> line;
      } else if (line == "POLYGON") {
        float x, y;
        std::vector<float> coord_x;
        std::vector<float> coord_y;
        while (myfile >> line) {
          if (is_float(line)) {
            x = std::stof(line);
            myfile >> y;
            coord_x.push_back(x);
            coord_y.push_back(y);
          } else {
            break;
          }
        }
        polygons->push_back(Polygon(coord_x, coord_y));
      } else {
        std::cout << "Unknown figure" << std::endl;
      }
    } while (!myfile.eof());
    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}
