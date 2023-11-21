#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

float f(float x) {
    return -2 * x * sin(x);
}

class PSO {
private:
    vector<float> x;
    vector<float> v;
    vector<float> c;
    vector<float> r;
    float w;
    vector<float> oldx;
    vector<float> pBest;
    float gBest;


public:
    PSO(vector<float> x_val, vector<float> v_val, vector<float> c_val, vector<float> r_val, float w_val) {
        x_val = x;
        v_val = v;
        c_val = c;
        r_val = r;
        w_val = w;

        oldx = x_val;
        pBest = {};
        gBest = 0.0;
    };

    void findPBest() {
        for(int i = 0; i < x.size(); i++) {
            if (f(x[i]) < f(pBest[i])) {
                pBest[i] = x[i];
            } else {
                pBest[i] = oldx[i];
            }
        }  
    }

    void findGBest() {
        vector<float> fValues;

        for (float x_val : x) {
            fValues.push_back(f(x_val));
        }
        auto min_it = min_element(fValues.begin(), fValues.end());
        int min_index = distance(fValues.begin(), min_it);

        gBest = x[min_index];
    }

    void updateV() {
        for(int i; i < x.size(); i++) {
            v[i] = (w * v[i]) + (c[0] * r[0] * (pBest[i] - x[i])) + (c[1] * r[1] *(gBest - x[i])) ;
        }
    }

    void updateX() {
        for(int i; i < x.size(); i++) {
            oldx[i] = x[i];
            x[i] += v[i];
        }
    }
};

int main() {
    cout << "Hello World" << endl;
    return 0;
}