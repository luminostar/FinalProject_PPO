#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double f(double x) {
    return -2 * x * sin(x);
}

class PSO {
private:
    vector<double> x, v, c, r, oldX, pBest;
    double w;
    double gBest;

public:
    PSO(vector<double> x_vals, vector<double> v_vals, vector<double> c_vals, vector<double> r_vals, double w_val) {
        x = x_vals;
        v = v_vals;
        c = c_vals;
        r = r_vals;
        w = w_val;

        oldX = x;
        pBest = x;
        gBest = 0.0;
    }

    void findPBest() {
        for (size_t i = 0; i < x.size(); ++i) {
            if (f(x[i]) < f(pBest[i])) {
                pBest[i] = x[i];
            } else {
                pBest[i] = oldX[i];
            }
        }
    }

    void findGBest() {
        double minVal = f(x[0]);
        int minIndex = 0; 

        for (int i = 1; i < x.size(); ++i) {
            double fx = f(x[i]);
            if (fx < minVal) {
                minVal = fx;
                minIndex = i;
            }
        }
        gBest = x[minIndex]; // Set gBest ke nilai x dengan indeks minimum
    }


    void updateV() {
        for (int i = 0; i < x.size(); ++i) {
            v[i] = (w * v[i]) + (c[0] * r[0] * (pBest[i] - x[i])) + (c[1] * r[1] * (gBest - x[i]));
        }
    }

    void updateX() {
        for (int i = 0; i < x.size(); ++i) {
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
        cout << endl << "f(x) = ";
        for (const auto& val : x) {
            cout << f(val) << " ";
        }
        cout << endl << "pBest = ";
        for (const auto& val : pBest) {
            cout << val << " ";
        }
        cout << endl << "gBest = " << gBest << endl << endl;
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Iterasi ke-" << i + 1 << endl;
            findPBest();
            findGBest();
            updateV();
            updateX();

            cout << "x = ";
            for (const auto& val : x) {
                cout << val << " ";
            }
            cout << endl << "v = ";
            for (const auto& val : v) {
                cout << val << " ";
            }
            cout << endl << "f(x) = ";
            for (const auto& val : x) {
                cout << f(val) << " ";
            }
            cout << endl <<"pBest = ";
            for (const auto& val : pBest) {
                cout << val << " ";
            }
            cout << endl << "gBest = " << gBest << endl << endl;
        }
    }

};

int main() {
    vector<double> x = {1.0, M_PI / 2, M_PI}; 
    vector<double> v = {0, 0, 0};
    vector<double> c = {0.5, 1.0}; 
    vector<double> r = {1.0, 1.0}; 
    double w = 1;

    PSO pso(x, v, c, r, w);
    pso.iterate(50);

    return 0;
}
