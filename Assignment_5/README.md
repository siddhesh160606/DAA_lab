# Assignment 5: Dynamic Programming for Multistage Graph Route Optimization (SwiftCargo)

- **Student Name**: Siddhesh Parkar
- **PRN**: 124B1F021
- **GitHub Repository**: [https://github.com/siddhesh160606/DAA_lab](https://github.com/siddhesh160606/DAA_lab)

## Aim
To implement Dynamic Programming for finding the most cost-efficient route in a directed weighted multistage graph for SwiftCargo, while handling multiple stages, dynamic route-cost updates, and batch delivery requests efficiently.

## Scenario
A logistics company, SwiftCargo, specializes in delivering packages across multiple cities. To optimize its delivery process, the company divides the transportation network into multiple stages such as warehouses, transit hubs, and final delivery points. Each package must follow the most cost-efficient or fastest route from the source to the destination while passing through the predefined stages.

## Algorithm & Recurrence Relation
Dynamic Programming is used to find the minimum cost from a node to the destination:
$$\text{dp}[u] = \min(\text{cost}(u, v) + \text{dp}[v])$$
- $\text{dp}[u]$: Minimum cost from node $u$ to destination
- $\text{cost}(u, v)$: Cost of travelling from node $u$ to node $v$
- $\text{dp}[\text{destination}] = 0$

## Complexity Analysis
- **Time Complexity**: $\mathcal{O}(V + E)$ where $V$ is the number of nodes and $E$ is the number of directed routes.
- **Space Complexity**: $\mathcal{O}(V + E)$ using adjacency list representation and auxiliary arrays ($\text{dp}[]$, $\text{parent}[]$, $\text{nodes}[][]$).

## Files
- `multistage.cpp`: Source code implementing multistage graph dynamic programming with real-time route update support.
- `output.txt`: Sample execution output demonstrating optimal delivery route computation and real-time cost update.

## Compilation & Execution
```bash
g++ multistage.cpp -o multistage
./multistage
```
