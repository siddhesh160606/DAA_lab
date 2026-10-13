/*
 * Student Name: Siddhesh Parkar
 * PRN: 124B1F021
 * GitHub Repository: https://github.com/siddhesh160606/DAA_lab
 * Assignment 6: Disaster Relief Resource Allocation Using Dynamic Programming (0/1 Knapsack with Priorities)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int weight;
    int utility;
    int priority;
};

// Returns a score based on utility and priority
int getScore(const Item& item) {
    return item.utility + (item.priority * 100);
}

int main() {
    cout << "Student Name : Siddhesh Parkar\n";
    cout << "PRN          : 124B1F021\n";
    cout << "GitHub Link  : https://github.com/siddhesh160606/DAA_lab\n";
    cout << "--------------------------------------------------------\n";

    int N, W;
    cout << "Enter number of items: ";
    cin >> N;

    cout << "Enter truck capacity: ";
    cin >> W;

    vector<Item> items(N);
    cout << "\nEnter item details:\n";
    cout << "Priority: 3 = Critical, 2 = High, 1 = Normal\n\n";

    for (int i = 0; i < N; i++) {
        cout << "Item " << i + 1 << " name: ";
        cin >> items[i].name;

        cout << "Weight: ";
        cin >> items[i].weight;

        cout << "Utility: ";
        cin >> items[i].utility;

        cout << "Priority: ";
        cin >> items[i].priority;
    }

    // DP table
    vector<vector<int>> dp(
        N + 1,
        vector<int>(W + 1, 0)
    );

    // Dynamic Programming
    for (int i = 1; i <= N; i++) {
        int score = getScore(items[i - 1]);
        for (int w = 0; w <= W; w++) {
            // Don't select the item
            dp[i][w] = dp[i - 1][w];

            // Select the item if it fits
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    score + dp[i - 1][w - items[i - 1].weight]
                );
            }
        }
    }

    // Find selected items
    vector<int> selected;
    int remainingCapacity = W;
    for (int i = N; i > 0; i--) {
        if (dp[i][remainingCapacity] != dp[i - 1][remainingCapacity]) {
            selected.push_back(i - 1);
            remainingCapacity -= items[i - 1].weight;
        }
    }

    reverse(selected.begin(), selected.end());

    // Sort selected items by priority
    sort(selected.begin(), selected.end(),
        [&](int a, int b) {
            if (items[a].priority != items[b].priority)
                return items[a].priority > items[b].priority;
            return items[a].utility > items[b].utility;
        });

    // Display result
    cout << "\n====================================\n";
    cout << " PRIORITY-WISE RELIEF ALLOCATION\n";
    cout << "====================================\n";

    int totalWeight = 0;
    int totalUtility = 0;

    for (int index : selected) {
        totalWeight += items[index].weight;
        totalUtility += items[index].utility;

        cout << "\nItem: " << items[index].name;
        cout << "\nWeight: " << items[index].weight << " kg";
        cout << "\nUtility: " << items[index].utility;
        cout << "\nPriority: " << items[index].priority;
        cout << "\n";
    }

    cout << "\n------------------------------------\n";
    cout << "Total Weight : " << totalWeight << " kg\n";
    cout << "Total Utility : " << totalUtility << "\n";
    cout << "Capacity : " << W << " kg\n";

    cout << "\nTime Complexity : O(N * W)";
    cout << "\nSpace Complexity: O(N * W)\n";

    return 0;
}
