#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double f(double x, double y) {
    return pow((x + y*y - 13) + (x*x + y - 9 ), 2);
}

class PSO {
private:
    vector<double> x, y, v, c, r, oldX, oldY, pBestx, pBesty;
    double w;
    double gBestx;
    double gBesty;

public:
    PSO(vector<double> x_vals, vector<double> y_vals, vector<double> v_vals, vector<double> c_vals, vector<double> r_vals, double w_val) {
        x = x_vals;
        y = y_vals;
        v = v_vals;
        c = c_vals;
        r = r_vals;
        w = w_val;

        oldX = x;
        oldY = y;
        pBestx = x;
        pBesty = y;
        gBestx = 0.0;
        gBesty = 0.0;
    }

    void findpBest() {
        for (size_t i = 0; i < x.size(); ++i) {
            value = f(x[i]. y[i])
            pBestValue = 
            if (f(x[i]) < f(pBestx[i])) {
                pBestx[i] = x[i];
            } else {
                pBestx[i] = oldX[i];
            }
        }
    }

    void findGBest() {
        double minVal = f(x[0]);
        size_t minIndex = 0; 

        for (size_t i = 1; i < x.size(); ++i) {
            double fx = f(x[i]);
            if (fx < minVal) {
                minVal = fx;
                minIndex = i;
            }
        }
        gBestx = x[minIndex];
    }


    void updateV() {
        for (size_t i = 0; i < x.size(); ++i) {
            v[i] = (w * v[i]) + (c[0] * r[0] * (pBestx[i] - x[i])) + (c[1] * r[1] * (gBestx - x[i]));
        }
    }

    void updateX() {
        for (size_t i = 0; i < x.size(); ++i) {
            oldX[i] = x[i];
            x[i] += v[i];
        }
    }

    void iterate(int n) {
        cout << "Iterasi ke-0" << endl;
        cout << "x = ";
        for (const auto& val : x) {
            cout << val << " ";
        }
        cout << endl << "v = ";
        for (const auto& val : v) {
            cout << val << " ";
        }
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Iterasi ke-" << i + 1 << endl;
            findpBest();
            findGBest();
            updateV();
            updateX();

            cout << "x = ";
            for (const auto& val : x) {
                cout << val << " ";
            }
            cout << endl << "f(x) = ";
            for (const auto& val : x) {
                cout << f(val) << " ";
            }
            cout << endl << endl;
        }
    }
};

int main() {
    vector<double> x = {1.0, M_PI / 2, M_PI}; 
    vector<double> v = {0, 0, 0};
    vector<double> c = {0.5, 1}; 
    vector<double> r = {1.0, 1.0}; 
    double w = 1;

    PSO pso(x, v, c, r, w);
    pso.iterate(100);

    return 0;
}