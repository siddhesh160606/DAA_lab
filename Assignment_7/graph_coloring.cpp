/*
 * Student Name: Siddhesh Parkar
 * PRN: 124B1F021
 * GitHub Repository: https://github.com/siddhesh160606/DAA_lab
 * Assignment 7: University Exam Timetable Scheduling Using Graph Coloring and Backtracking
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

bool isSafe(int v, int color,
            const vector<vector<int>>& graph,
            const vector<int>& colors)
{
    for (int u : graph[v]) {
        if (colors[u] == color)
            return false;
    }
    return true;
}

bool graphColoring(int v, int n, int k,
                   const vector<vector<int>>& graph,
                   vector<int>& colors)
{
    if (v == n)
        return true;

    for (int color = 1; color <= k; color++) {
        if (isSafe(v, color, graph, colors)) {
            colors[v] = color;
            if (graphColoring(v + 1, n, k, graph, colors))
                return true;
            colors[v] = 0;
        }
    }
    return false;
}

int findMinimumSlots(const vector<vector<int>>& graph,
                     vector<int>& result)
{
    int n = graph.size();
    for (int k = 1; k <= n; k++) {
        vector<int> colors(n, 0);
        if (graphColoring(0, n, k, graph, colors)) {
            result = colors;
            return k;
        }
    }
    return n;
}

int main() {
    cout << "Student Name : Siddhesh Parkar\n";
    cout << "PRN          : 124B1F021\n";
    cout << "GitHub Link  : https://github.com/siddhesh160606/DAA_lab\n";
    cout << "--------------------------------------------------------\n";

    int n, rooms, edges, pairs;
    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of rooms: ";
    cin >> rooms;

    vector<string> course(n);
    cout << "\nEnter course names:\n";
    for (int i = 0; i < n; i++) {
        cout << "Course " << i + 1 << ": ";
        cin >> course[i];
    }

    vector<vector<int>> graph(n);
    cout << "\nEnter number of conflict edges: ";
    cin >> edges;

    cout << "Enter conflict edges (course numbers):\n";
    cout << "Example: 1 2 means Course 1 conflicts with Course 2\n";
    for (int i = 0; i < edges; i++) {
        cout << "Edge " << i + 1 << ": ";
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "\nEnter number of course pairs having common students: ";
    cin >> pairs;

    cout << "Enter course pairs having common students:\n";
    cout << "Example: 1 3 means courses 1 and 3 have common students\n";
    for (int i = 0; i < pairs; i++) {
        cout << "Pair " << i + 1 << ": ";
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> colors;
    int slots = findMinimumSlots(graph, colors);

    cout << "\n=======================================================\n";
    cout << "           OPTIMAL EXAM TIMETABLE ALLOCATION           \n";
    cout << "=======================================================\n";
    cout << "Minimum Required Exam Time Slots (Chromatic No.): " << slots << "\n";

    vector<string> assignedRoom(n);

    for (int slot = 1; slot <= slots; slot++) {
        cout << "\n>>> TIME SLOT " << slot << ":\n";
        int room = 1;
        for (int i = 0; i < n; i++) {
            if (colors[i] == slot) {
                if (room <= rooms) {
                    cout << "    [Classroom " << room << "] -> " << course[i] << " (Scheduled)\n";
                    assignedRoom[i] = "Room " + to_string(room);
                    room++;
                }
                else {
                    cout << "    [OVERFLOW]     -> " << course[i] << " (No classroom available!)\n";
                    assignedRoom[i] = "Overflow (No Room)";
                }
            }
        }
    }

    cout << "\n=======================================================\n";
    cout << "             COURSE SCHEDULE SUMMARY TABLE             \n";
    cout << "=======================================================\n";
    cout << left << setw(18) << "Course Name" << setw(18) << "Assigned Slot" << "Allocated Room" << endl;
    cout << "-------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(18) << course[i]
             << setw(18) << ("Slot " + to_string(colors[i]))
             << assignedRoom[i] << endl;
    }
    cout << "=======================================================\n";

    return 0;
}
