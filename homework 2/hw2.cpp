#include <iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

double get_x(ifstream &file) {
    string xstr;
    double x;
    file >> xstr;
    x = stod(xstr);
    return x;
}

double get_y(ifstream& file) {
    string ystr;
    double y;
    file >> ystr;
    y = stod(ystr);
    return y;
}

double H_t(double h0, double vy, double t) {
    double Ht = h0 + vy * t - ((9.81 * t * t) / 2);
    return Ht;
}

double vvy(double vy0, double t) {
    double vvy = vy0 - 9.81 * t;
    return vvy;
}

void get_h0(ifstream &file, double &h) {
    string temp;
    file >> temp;
    h = stod(temp);
}

void get_v0(ifstream &file, double &vx, double &vy) {
    string v1, v2;
    file >> v1 >> v2;
    vx = stod(v1);
    vy = stod(v2);
}

void stolbi(ifstream &file, vector<double> &X, vector<double> &H) {
    string x, h;
    file >> x >> ws >> h;
    X.push_back(stod(x));
    H.push_back(stod(h));
}

void funct(double x0, double h0, double vx, double vy, vector<double> &X, vector<double> &H, int &res, int delta) {
    double t, y;
    for (int i = res; (i > -1 && i < X.size()); i = i + delta)
    {
        t = (X[i + delta] - x0) / (delta * vx);
        y = H_t(h0, vy, t);
        if (H[i + delta] < y) {
            res += delta;
        }
        else if ((y < 0) || (res == 0)) {
            return;
        }
        else
        {
            double vyt = vvy(vy, t);
            delta = delta * -1;
            funct(X[i], y, vx, vyt, X, H, res, delta);
            return;
        }
    }
}

void calculation(ifstream &file, double &h0, double &vx, double &vy, vector<double> &X, vector<double> &H, int &res) {
    string line;
    double t;
    double y;
    while (getline(file, line)) {
        stolbi(file, X, H);
        t = X.back() / vx;
        y = H_t(h0, vy, t);
        if (H.back() < y)
        {
            res++;
        }
        else if ((y < 0) || (res == 0))
        {
            return;
        }
        else
        {
            double vyt = vvy(vy, t);
            funct(X.back(), y, vx, vyt, X, H, res, -1);
            return;
        }
    }
}


int main(int argc, char** argv) {
    string filename;

    if (argc == 2)
    {
        filename = argv[1];
    }
    else {
        filename = "in.txt";
    }
    ifstream input_file(filename);

    double h0, vx, vy;
    int res = 0;
    int i = 0;
    string line;

    vector<double> X;
    vector<double> H;

    get_h0(input_file, h0);
    get_v0(input_file, vx, vy);

    calculation(input_file, h0, vx, vy, X, H, res);

    cout << res << endl;
    return 0;
}
