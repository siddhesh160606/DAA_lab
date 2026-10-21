/*
 * Student Name: Siddhesh Parkar
 * PRN: 124B1F021
 * GitHub Repository: https://github.com/siddhesh160606/DAA_lab
 * Assignment 4: Ambulance Route Optimization to Nearest Hospital using Dijkstra's Algorithm
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

void dijkstra(int source, const vector<vector<pair<int, int>>> &graph, vector<int> &dist, vector<int> &parent) {
    int V = graph.size();
    dist.assign(V, INT_MAX);
    parent.assign(V, -1);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (const auto &edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<int> getPath(int dest, const vector<int> &parent) {
    vector<int> path;
    for (int cur = dest; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    cout << "Student Name : Siddhesh Parkar\n";
    cout << "PRN          : 124B1F021\n";
    cout << "GitHub Link  : https://github.com/siddhesh160606/DAA_lab\n";
    cout << "--------------------------------------------------------\n";

    int V, E;
    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<pair<int, int>>> graph(V);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected road
    }

    int source;
    cout << "\nEnter ambulance start location (source): ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;

    vector<int> hospitals(H);
    cout << "Enter hospital nodes: ";
    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    vector<int> dist;
    vector<int> parent;
    dijkstra(source, graph, dist, parent);

    cout << "\n=======================================================\n";
    cout << "             SHORTEST TRAVEL TIME TO ALL NODES         \n";
    cout << "=======================================================\n";
    cout << left << setw(15) << "Intersection" << setw(20) << "Travel Time (min)" << "Path from Ambulance" << endl;
    cout << "-------------------------------------------------------\n";
    for (int i = 0; i < V; i++) {
        cout << left << setw(15) << i;
        if (dist[i] == INT_MAX) {
            cout << setw(20) << "Unreachable" << "-" << endl;
        } else {
            cout << setw(20) << dist[i];
            vector<int> p = getPath(i, parent);
            for (size_t k = 0; k < p.size(); k++) {
                cout << p[k] << (k + 1 < p.size() ? " -> " : "");
            }
            cout << endl;
        }
    }

    cout << "\n=======================================================\n";
    cout << "               HOSPITAL EVALUATION SUMMARY             \n";
    cout << "=======================================================\n";
    cout << left << setw(15) << "Hospital Node" << setw(20) << "Travel Time (min)" << "Optimal Navigation Path" << endl;
    cout << "-------------------------------------------------------\n";

    int minTime = INT_MAX, nearestHospital = -1;
    for (int h : hospitals) {
        cout << left << setw(15) << h;
        if (dist[h] == INT_MAX) {
            cout << setw(20) << "Unreachable" << "No route available" << endl;
        } else {
            cout << setw(20) << dist[h];
            vector<int> p = getPath(h, parent);
            for (size_t k = 0; k < p.size(); k++) {
                cout << p[k] << (k + 1 < p.size() ? " -> " : "");
            }
            cout << endl;
            if (dist[h] < minTime) {
                minTime = dist[h];
                nearestHospital = h;
            }
        }
    }
    cout << "-------------------------------------------------------\n";

    if (nearestHospital == -1) {
        cout << "CRITICAL ALERT: No hospital reachable from current location!\n";
    } else {
        cout << ">>> BEST DESTINATION: Nearest hospital is at Node " << nearestHospital
             << " with minimum travel time of " << minTime << " minutes.\n";
        cout << ">>> DISPATCH ROUTE  : ";
        vector<int> bestP = getPath(nearestHospital, parent);
        for (size_t k = 0; k < bestP.size(); k++) {
            cout << bestP[k] << (k + 1 < bestP.size() ? " -> " : "");
        }
        cout << "\n=======================================================\n";
    }

    // Dynamic Traffic Update
    char updateChoice;
    cout << "\nSimulate dynamic road congestion / traffic update? (y/n): ";
    cin >> updateChoice;

    if (updateChoice == 'y' || updateChoice == 'Y') {
        int u, v, newWeight;
        cout << "Enter road segment to update (u v new_weight): ";
        cin >> u >> v >> newWeight;

        bool updated = false;
        for (auto &edge : graph[u]) {
            if (edge.first == v) {
                edge.second = newWeight;
                updated = true;
            }
        }
        for (auto &edge : graph[v]) {
            if (edge.first == u) {
                edge.second = newWeight;
                updated = true;
            }
        }

        if (updated) {
            cout << "\n[Traffic Update Applied]: Travel time between " << u << " and " << v << " changed to " << newWeight << " minutes.\n";
            dijkstra(source, graph, dist, parent);

            int newMinTime = INT_MAX, newNearestHospital = -1;
            for (int h : hospitals) {
                if (dist[h] < newMinTime) {
                    newMinTime = dist[h];
                    newNearestHospital = h;
                }
            }

            cout << "\n=======================================================\n";
            cout << "       RECALCULATED EMERGENCY ROUTE AFTER TRAFFIC      \n";
            cout << "=======================================================\n";
            cout << ">>> RE-ROUTED DESTINATION : Nearest hospital is Node " << newNearestHospital << endl;
            cout << ">>> NEW TRAVEL TIME       : " << newMinTime << " minutes" << endl;
            cout << ">>> NEW DISPATCH ROUTE    : ";
            vector<int> p = getPath(newNearestHospital, parent);
            for (size_t k = 0; k < p.size(); k++) {
                cout << p[k] << (k + 1 < p.size() ? " -> " : "");
            }
            cout << "\n=======================================================\n";
        } else {
            cout << "Error: Road segment not found.\n";
        }
    }

    return 0;
}
