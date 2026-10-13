# Assignment 7: University Exam Timetable Scheduling Using Graph Coloring and Backtracking

- **Student Name**: Siddhesh Parkar
- **PRN**: 124B1F021
- **GitHub Repository**: [https://github.com/siddhesh160606/DAA_lab](https://github.com/siddhesh160606/DAA_lab)

## Title & Introduction
University examination scheduling requires arranging course examinations without conflicts so that no student enrolled in two courses has exams scheduled at the same time slot. This problem is modeled as **Graph Coloring**:
- **Vertex**: Course
- **Edge**: Common students between two courses (conflict)
- **Color**: Examination time slot
- **Rooms**: Physical room capacity per slot

## Objectives
1. Model exam schedule as an undirected conflict graph.
2. Implement Backtracking Graph Coloring to determine the minimum number of time slots ($k$).
3. Eliminate scheduling clashes.
4. Allocate courses to available examination rooms per time slot.

## Algorithm - Backtracking Graph Coloring
1. Test for $k = 1, 2, \dots, n$ slots sequentially.
2. Recursively assign available colors $(1 \dots k)$ to vertices:
   - For course $v$, check if `color` is safe against all adjacent courses.
   - If safe, assign `colors[v] = color` and recurse to course $v + 1$.
   - If recursion succeeds, return `true`.
   - Otherwise, backtrack (`colors[v] = 0`) and try the next color.
3. The smallest $k$ that yields a valid coloring gives the optimal number of slots.

## Comparison of Graph Coloring Techniques
| Feature | Greedy Coloring | Welsh-Powell | DSATUR |
| :--- | :--- | :--- | :--- |
| **Method** | Assigns first available color | Sorts courses by decreasing degree | Selects course with highest saturation |
| **Speed** | Very Fast | Fast | Moderate |
| **Course Order** | Input order | Highest degree first | Dynamic |
| **Color Usage** | May use more colors | Improves over simple order | Often produces near-optimal colorings |
| **Time Complexity** | $\mathcal{O}(V + E)$ approx. | $\mathcal{O}(V \log V + E)$ approx. | $\mathcal{O}(V^2 + E)$ approx. |
| **Minimum Colors Guaranteed?** | No | No | No (Heuristic) |

## Complexity Analysis
- **Time Complexity**: $\mathcal{O}(k^V)$ in the worst case using Backtracking (finds optimal chromatic number).
- **Space Complexity**: $\mathcal{O}(V + E)$ for adjacency list and coloring array.

## Files
- `graph_coloring.cpp`: Source code implementing Backtracking Graph Coloring with room constraint allocation.
- `output.txt`: Sample execution output demonstrating clash-free exam timetable generation.

## Compilation & Execution
```bash
g++ graph_coloring.cpp -o graph_coloring
./graph_coloring
```
