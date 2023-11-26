#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

double f(double x, double y) {
    return pow((x + y*y - 13), 2) + pow((x*x + y - 9), 2);
}

class PSO {
private:
    vector<double> x, y, vx, vy, c, r, oldX, oldY, pBestX, pBestY;
    double w;
    double gBestX;
    double gBestY;

public:
    PSO(vector<double> x_vals, vector<double> y_vals, vector<double> v_vals, vector<double> c_vals, vector<double> r_vals, double w_val) {
        x = x_vals;
        y = y_vals;
        vx = v_vals;
        vy = v_vals;
        c = c_vals;
        r = r_vals;
        w = w_val;

        oldX = x;
        oldY = y;
        pBestX = x;
        pBestY = y;
        gBestX = x[min_element(x.begin(), x.end()) - x.begin()];
        gBestY = y[min_element(y.begin(), y.end()) - y.begin()];

    }

    void findpBest() {
        for (int i = 0; i < x.size(); ++i) {
            double value = f(x[i], y[i]);
            double pBestValue = f(pBestX[i], pBestY[i]);
            if (value < pBestValue) {
                pBestX[i] = x[i];
                pBestY[i] = y[i];
            } else {
                pBestX[i] = oldX[i];
                pBestY[i] = oldY[i];
            }
        }
    }

    void findGBest() {
        vector<double> fValues;

        for(int i = 0; i < x.size(); i++) {
            fValues.push_back(f(x[i], y[i]));
        }

        auto minimumIndex = min_element(fValues.begin(), fValues.end()) - fValues.begin();

        gBestX = x[minimumIndex];
        gBestY = y[minimumIndex];
    }


    void updateV() {
        for (int i = 0; i < x.size(); ++i) {
            vx[i] = (w * vx[i]) + (c[0] * r[0] * (pBestX[i] - x[i])) + (c[1] * r[1] * (gBestX - x[i]));
            vy[i] = (w * vy[i]) + (c[0] * r[0] * (pBestY[i] - y[i])) + (c[1] * r[1] * (gBestY - y[i]));
        }
    }

    void updateX() {
        for (int i = 0; i < x.size(); ++i) {
            oldX[i] = x[i];
            oldY[i] = y[i];
            x[i] += vx[i];
            y[i] += vy[i];
        }
    }

    void iterate(int n) {
        cout << "Inisialisasi\n";
        
        cout << "x = ";
        for (const auto& val : x) {
            cout << val << " ";
        }
        cout << endl << "y = ";
        for (const auto& val : y) {
            cout << val << " ";
        }
        cout << endl << "vx = ";
        for (const auto& val : vx) {
            cout << val << " ";
        }
        cout << endl << "vy = ";
        for (const auto& val : vy) {
            cout << val << " ";
        }
        cout << endl << "vy = ";
        for (const auto& val : vy) {
            cout << val << " ";
        }
        cout << endl << "c = ";
        for (const auto& val : c) {
            cout << val << " ";
        }
        cout << endl << "r = ";
        for (const auto& val : r) {
            cout << val << " ";
        }
        cout << endl << "w = " << w;
        cout << endl;
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Iterasi ke-" << i + 1 << endl;
            cout << "x = ";
            for (const auto& val : x) {
                cout << val << " ";
            }
            cout << endl << "y = ";
            for (const auto& val : y) {
                cout << val << " ";
            }
            cout << endl << "vx = ";
            for (const auto& val : vx) {
                cout << val << " ";
            }
            cout << endl << "vy = ";
            for (const auto& val : vy) {
                cout << val << " ";
            }
            cout << endl <<"f(x,y) = ";
            for (int i = 0; i < x.size() && i < y.size(); ++i) {
                cout << f(x[i], y[i]) << " ";
            }

            findpBest();
            findGBest();

            cout << endl << "pBestX = ";
            for (const auto& val : pBestX) {
                cout << val << " ";
            }
            cout << endl << "gBestX = " << gBestX;

            cout << endl << "pBestY = ";
            for (const auto& val : pBestY) {
                cout << val << " ";
            }
            cout << endl << "gBestY = " << gBestY << endl;

            updateV();
            updateX();

            cout << endl <<"Updated x = ";
            for (const auto &val : x) {
                cout << val << " ";
            }
            cout << endl << "Updated y = ";
            for (const auto &val : y) {
                cout << val << " ";
            }
            cout << endl << "Updated vx = ";
            for (const auto &val : vx) {
                cout << val << " ";
            }
            cout << endl << "Updated vy = ";
            for (const auto &val : vy) {
                cout << val << " ";
            }
            cout << "\n";
            cout << "\n";
        }
    }
};

int main() {
    vector<double> x = {1.0, -1.0, 2.0};
    vector<double> y = {1.0, -1.0, 1.0};
    vector<double> vx = {0, 0, 0};
    vector<double> vy = {0, 0, 0};
    vector<double> c = {1.0, 0.5}; 
    vector<double> r = {1.0, 1.0};
    double w = 1.0;

    PSO pso(x, y, vx, c, r, w);
    pso.iterate(3);

    return 0;
}