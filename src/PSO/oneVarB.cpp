#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <random>

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
        for (int i = 0; i < x.size(); ++i) {
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
        gBest = x[minIndex]; 
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

    void iterate(int n, double tolerance) {
        double prevBest = f(gBest); // Simpan nilai fungsi objektif pada iterasi sebelumnya
        int unchangedCount = 0; // Hitung berapa kali nilai fungsi objektif tidak berubah

        cout << "Inisialisasi\n";

        cout << "x = ";
        for (const auto &val : x) {
            cout << val << " ";
        }
        cout << endl << "v = ";
        for (const auto &val : v) {
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
        cout << "\n";
        cout << "\n";

        for (int i = 0; i < n; ++i) {
            cout << "Iterasi ke-" << i + 1 << endl;
            cout << "x = ";
            for (const auto &val : x) {
                cout << val << " ";
            }
            cout << endl << "v = ";
            for (const auto &val : v) {
                cout << val << " ";
            }
            cout << endl << "f(x) = ";
            for (const auto &val : x) {
                cout << f(val) << " ";
            }
            findPBest();
            findGBest();
            cout << endl << "pBest = ";
            for (const auto &val : pBest) {
                cout << val << " ";
            }

            cout << endl << "gBest = " << gBest << endl << endl;

            updateV();
            updateX();

            cout << "Updated x = ";
            for (const auto &val : x) {
                cout << val << " ";
            }
            cout << endl << "Updated v = ";
            for (const auto &val : v) {
                cout << val << " ";
            }

            double currentBest = f(gBest); // Hitung nilai fungsi objektif pada iterasi saat ini

            // Periksa perbedaan nilai fungsi objektif antara iterasi saat ini dan sebelumnya
            if (abs(currentBest - prevBest) < tolerance) {
                unchangedCount++; // Jika perbedaannya kecil, tambahkan hitungan nilai yang tidak berubah
            } else {
                unchangedCount = 0; // Jika ada perubahan, reset hitungan nilai yang tidak berubah
            }

            // Jika nilai fungsi objektif tidak berubah dalam beberapa iterasi, hentikan iterasi
            if (unchangedCount >= 5) { // Misalnya, hentikan setelah 5 iterasi tanpa perubahan (sesuaikan sesuai kebutuhan)
                cout << endl << "Iterasi dihentikan karena konvergensi telah tercapai." << endl;
                break;
            }

            prevBest = currentBest; // Simpan nilai fungsi objektif pada iterasi sebelumnya untuk iterasi berikutnya
            cout << "\n";
            cout << "\n";
        }
    }
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disVar(0.0, M_PI);
    uniform_real_distribution<> disR(0, 1);

    vector<double> x ;
    for (int i = 0; i < 3; ++i) {
        double randNumX = disVar(gen);
        x.push_back(randNumX);
    } 
    vector<double> v;
    for (int i = 0; i < 3; ++i) {
        v.push_back(0);
    }
    vector<double> c = {0.5, 1.0}; 
    vector<double> r;
    for (int i = 0; i < 2; ++i) {
        double randNumR = disR(gen);
        r.push_back(randNumR);
    }
    double w = 1;

    double tolerance = 1e-5; // Tentukan nilai toleransi untuk konvergensi

    PSO pso(x, v, c, r, w);
    pso.iterate(200, tolerance); // Ubah menjadi fungsi iterate dengan tambahan parameter tolerance

    return 0;
}
