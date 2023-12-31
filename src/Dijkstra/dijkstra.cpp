#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Dijkstra {
private:
    int** cost;
    int n;

public:
    Dijkstra(int** costMatrix, int vertices) {
        n = vertices;
        cost = costMatrix;
    }

    int getMin(int dist[], bool visited[]) {
        int key = 0;
        int min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                key = i;
            }
        }
        return key;
    }

    void display(int dist[], int par[]) {
        for (int i = 0; i < n; i++) {
            int temp = par[i];
            cout << i << " <- ";
            while (temp != -1) {
                cout << temp << " <- ";
                temp = par[temp];
            }
            cout << endl;
            cout << "::::Distance = " << dist[i];
            cout << endl;
        }
    }

    void dijkstra(int src) {
        int par[100], dist[100];
        bool visited[100] = {0};
        fill(dist, dist + n, INT_MAX);

        dist[src] = 0;
        par[src] = -1;

        for (int g = 0; g < n - 1; g++) {
            int u = getMin(dist, visited);
            visited[u] = true;
            cout << " min = " << u << endl;
            for (int v = 0; v < n; v++) {
                if (!visited[v] && (dist[u] + cost[u][v]) < dist[v] && cost[u][v] != 9999) {
                    par[v] = u;
                    dist[v] = dist[u] + cost[u][v];
                }
            }
        }

        display(dist, par);
    }
};

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    int** costMatrix = new int*[n];
    for (int i = 0; i < n; i++) {
        costMatrix[i] = new int[n];
    }

    cout << "Enter cost matrix: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> costMatrix[i][j];
    }

    int src;
    cout << "\nEnter source: ";
    cin >> src;

    Dijkstra dijkstraAlgo(costMatrix, n);
    dijkstraAlgo.dijkstra(src);

    // Deallocation of memory
    for (int i = 0; i < n; i++) {
        delete[] costMatrix[i];
    }
    delete[] costMatrix;

    return 0;
}
