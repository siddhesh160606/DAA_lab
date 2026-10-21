/*
 * Student Name: Siddhesh Parkar
 * PRN: 124B1F021
 * GitHub Repository: https://github.com/siddhesh160606/DAA_lab
 * Assignment 5: Dynamic Programming for Multistage Graph Route Optimization (SwiftCargo)
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int cost;
};

int main() {
    cout << "Student Name : Siddhesh Parkar\n";
    cout << "PRN          : 124B1F021\n";
    cout << "GitHub Link  : https://github.com/siddhesh160606/DAA_lab\n";
    cout << "--------------------------------------------------------\n";

    int stages;
    cout << "SWIFTCARGO LOGISTICS OPTIMIZATION\n";
    cout << "---------------------------------\n";
    cout << "Enter number of stages: ";
    cin >> stages;

    vector<vector<int>> nodes(stages);
    for (int i = 0; i < stages; i++) {
        int n;
        cout << "Enter number of nodes in stage " << i + 1 << ": ";
        cin >> n;
        nodes[i].resize(n);
        cout << "Enter node IDs: ";
        for (int j = 0; j < n; j++) {
            cin >> nodes[i][j];
        }
    }

    vector<vector<Edge>> graph(1000);
    int routes;
    cout << "\nEnter number of routes: ";
    cin >> routes;

    cout << "Enter routes as: from to cost\n";
    for (int i = 0; i < routes; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        // Directed graph
        graph[u].push_back({v, c});
    }

    int source, destination;
    cout << "\nEnter source: ";
    cin >> source;
    cout << "Enter destination: ";
    cin >> destination;

    // Dynamic Programming
    vector<int> dp(1000, INT_MAX);
    vector<int> parent(1000, -1);
    dp[source] = 0;

    // Process stages forward
    for (int s = 0; s < stages - 1; s++) {
        for (int i = 0; i < (int)nodes[s].size(); i++) {
            int u = nodes[s][i];
            if (dp[u] == INT_MAX)
                continue;
            for (int j = 0; j < (int)graph[u].size(); j++) {
                int v = graph[u][j].to;
                int cost = graph[u][j].cost;
                if (dp[u] + cost < dp[v]) {
                    dp[v] = dp[u] + cost;
                    parent[v] = u;
                }
            }
        }
    }

    if (dp[destination] == INT_MAX) {
        cout << "\nNo valid route exists.\n";
        return 0;
    }

    // Construct optimal path
    vector<int> path;
    for (int x = destination; x != -1; x = parent[x]) {
        path.push_back(x);
    }
    reverse(path.begin(), path.end());

    cout << "\n========== INITIAL RESULT ==========\n";
    cout << "Minimum Delivery Cost: " << dp[destination] << endl;
    cout << "Optimal Route: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i != (int)path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
    cout << "====================================\n";

    // Real-time update
    char choice;
    cout << "\nUpdate route cost due to traffic/weather? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int u, v, newCost;
        cout << "Enter route (from to new_cost): ";
        cin >> u >> v >> newCost;

        bool found = false;
        for (int i = 0; i < (int)graph[u].size(); i++) {
            if (graph[u][i].to == v) {
                graph[u][i].cost = newCost;
                found = true;
            }
        }

        if (found) {
            cout << "\n[Route Cost Updated]: Edge " << u << " -> " << v << " now has cost " << newCost << endl;

            // Recalculate DP
            fill(dp.begin(), dp.end(), INT_MAX);
            fill(parent.begin(), parent.end(), -1);
            dp[source] = 0;

            for (int s = 0; s < stages - 1; s++) {
                for (int i = 0; i < (int)nodes[s].size(); i++) {
                    int u_node = nodes[s][i];
                    if (dp[u_node] == INT_MAX)
                        continue;
                    for (int j = 0; j < (int)graph[u_node].size(); j++) {
                        int v_node = graph[u_node][j].to;
                        int cost_edge = graph[u_node][j].cost;
                        if (dp[u_node] + cost_edge < dp[v_node]) {
                            dp[v_node] = dp[u_node] + cost_edge;
                            parent[v_node] = u_node;
                        }
                    }
                }
            }

            if (dp[destination] == INT_MAX) {
                cout << "\nNo valid route exists after update.\n";
            } else {
                vector<int> newPath;
                for (int x = destination; x != -1; x = parent[x]) {
                    newPath.push_back(x);
                }
                reverse(newPath.begin(), newPath.end());

                cout << "\n========== RECALCULATED RESULT ==========\n";
                cout << "New Minimum Delivery Cost: " << dp[destination] << endl;
                cout << "New Optimal Route: ";
                for (int i = 0; i < (int)newPath.size(); i++) {
                    cout << newPath[i];
                    if (i != (int)newPath.size() - 1)
                        cout << " -> ";
                }
                cout << "\n=========================================\n";
            }
        } else {
            cout << "Route not found.\n";
        }
    }

    return 0;
}
