#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

double get_x(ifstream& input_file) {
	double x;
	string xstr;

	input_file >> xstr;
	x = stod(xstr);

	return x;
}

double get_y(ifstream& input_file) {
	double y;
	string ystr;

	input_file >> ws >> ystr;
	y = stod(ystr);

	return y;
}

double length(double xn, double yn, double x, double y) {
	double lgth = abs((xn * y - x * yn) / (sqrt(xn * xn + yn * yn)));
	return lgth;
}

int PravoIliLevo(double xn, double yn, double x, double y) {
	if ((xn * y - x * yn) > 0) {
		return 1;
	}
	if ((xn * y - yn * x) < 0) {
		return 0;
	}
	if ((xn * y - yn * x) == 0) {
		return 1;
	}
}

int main() {
	ifstream file("in.txt");
	double leftx = 0; double lefty = 0; double rightx = 0; double righty = 0; double givenx = 0; double giveny = 0; double x = 0; double y = 0;
	string s;

	givenx = get_x(file);
	giveny = get_y(file);

	// cout << givenx;

	while (getline(file, s)) {
		x = get_x(file);
		y = get_y(file);
		if ((PravoIliLevo(givenx,giveny,x,y) == 1)) {
			if ((length(givenx, giveny, leftx, lefty)) < (length(givenx, giveny, x, y))) {
				leftx = x;
				lefty = y;
			}
		}
		if ((PravoIliLevo(givenx, giveny, x, y) == 0)) {
			if ((length(givenx, giveny, rightx, righty)) < (length(givenx, giveny, x, y))) {
				rightx = x;
				righty = y;
			}
		}

	}
	cout << "Leftmost: " << leftx << " " << lefty << "\n" << "Rightmost: " << rightx << " " << righty << endl;
	file.close();
	return 0;
	// Победа на классе uwu
}