# Assignment 6: Disaster Relief Resource Allocation Using Dynamic Programming (0/1 Knapsack)

- **Student Name**: Siddhesh Parkar
- **PRN**: 124B1F021
- **GitHub Repository**: [https://github.com/siddhesh160606/DAA_lab](https://github.com/siddhesh160606/DAA_lab)

## Title & Introduction
When a natural disaster such as an earthquake occurs, relief organizations need to transport essential supplies such as medicines, food, drinking water, blankets, and hygiene kits to affected areas within limited truck capacities. This problem is modeled as a **0/1 Knapsack Problem with Priority Weighting** and solved optimally using Dynamic Programming.

## Problem Statement
A relief truck has a maximum capacity of $W$ kg. There are $N$ different relief items, each having:
- A weight ($w_i$)
- A utility value representing its importance
- A priority level ($3 = \text{Critical}, 2 = \text{High}, 1 = \text{Normal}$)

Each item can either be selected (1) or not selected (0). The objective is to maximize the priority-weighted utility without exceeding capacity $W$.

## Scoring Function & Recurrence Relation
$$\text{Score}(\text{item}) = \text{utility} + (\text{priority} \times 100)$$

$$\text{DP}[i][w] = \begin{cases} \text{DP}[i-1][w] & \text{if } w_i > w \\ \max(\text{DP}[i-1][w], \, \text{Score}_i + \text{DP}[i-1][w - w_i]) & \text{if } w_i \le w \end{cases}$$

## Algorithm Comparison
| Algorithm | Time Complexity | Optimal Solution? | Advantage | Disadvantage |
| :--- | :--- | :---: | :--- | :--- |
| **Brute Force** | $\mathcal{O}(2^N)$ | Yes | Simple | Infeasible for large $N$ |
| **Dynamic Programming** | $\mathcal{O}(N \times W)$ | Yes | Efficient & guarantees optimum | Memory depends on capacity $W$ |
| **Greedy Approach** | $\mathcal{O}(N \log N)$ | No | Very fast | Suboptimal for 0/1 knapsack |

## Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N \times W)$
- **Space Complexity**: $\mathcal{O}(N \times W)$ for the DP table

## Files
- `knapsack_dp.cpp`: Source code implementing 0/1 Knapsack with priority weighting and backtrack path reconstruction.
- `output.txt`: Comprehensive execution output demonstrating optimal item selection across 8 relief supplies under 150 kg truck capacity.

## Compilation & Execution
```bash
g++ knapsack_dp.cpp -o knapsack_dp
./knapsack_dp
```
