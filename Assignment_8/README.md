# Assignment 8: Travelling Salesman Problem (TSP) using Least Cost Branch and Bound (SwiftShip)

- **Student Name**: Siddhesh Parkar
- **PRN**: 124B1F021
- **GitHub Repository**: [https://github.com/siddhesh160606/DAA_lab](https://github.com/siddhesh160606/DAA_lab)

## Title & Aim
To implement the **Least Cost Branch and Bound algorithm** for the Travelling Salesman Problem (TSP) to find the optimal delivery route for SwiftShip logistics company. The objective is to visit each customer city exactly once, return to the starting city, and minimize the total delivery/fuel cost while tracking total delivery time.

## Problem Statement
SwiftShip delivery trucks must traverse an optimal Hamiltonian tour across $N$ cities. While a Brute Force approach checks all $(N-1)!$ possible permutations (which quickly becomes intractable), the **Least Cost Branch and Bound** approach evaluates promising partial paths and eliminates unpromising search spaces using lower bound pruning.

## Lower Bound & Pruning Strategy
For any partial tour, a lower-bound estimate is computed:
$$\text{Lower Bound} = \text{Current Tour Cost} + \sum_{i \in \text{Unvisited Cities}} \min_{j \neq i}(\text{cost}[i][j])$$

**Pruning Rule:**
$$\text{If } \text{Lower Bound} \ge \text{Best Known Complete Cost} \implies \text{Prune branch}$$

## Algorithm Comparison
| Approach | Time Complexity | Pruning Efficiency |
| :--- | :--- | :--- |
| **Brute Force TSP** | $\mathcal{O}(N!)$ | None (checks all tours) |
| **Least Cost Branch and Bound (Worst-case)** | $\mathcal{O}(N!)$ | Explores full state space if no early cutoff |
| **Least Cost Branch and Bound (Practical)** | $\ll \mathcal{O}(N!)$ | High (substantially pruned branches) |

## Complexity Analysis
- **Time Complexity**: $\mathcal{O}(N!)$ worst case; substantially faster on average due to lower-bound pruning.
- **Space Complexity**: $\mathcal{O}(N^2)$ for storing distance/cost matrix, time matrix, and active recursion states.

## Files
- `tsp_branch_and_bound.cpp`: Source code implementing LC Branch and Bound TSP with cost and time matrix tracking and interactive menu.
- `output.txt`: Sample execution output demonstrating optimal tour computation:
  `City 1 -> City 2 -> City 3 -> City 1` with Minimum Cost: `22` and Total Delivery Time: `70`.

## Compilation & Execution
```bash
g++ tsp_branch_and_bound.cpp -o tsp_branch_and_bound
./tsp_branch_and_bound
```
