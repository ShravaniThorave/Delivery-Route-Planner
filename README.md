# Delivery Route Planner with Negative-Cost Adjustments

A C-based route planning program that uses the **Bellman-Ford algorithm** to find shortest paths in a directed weighted graph, including graphs containing negative edge weights.

The program also detects **reachable negative cycles** and identifies vertices for which no finite shortest path exists.

## Problem Statement

Develop a route-planning program that finds shortest paths even when some edges have negative weights and reports any reachable negative cycle.

Negative edge weights can represent situations such as discounts, rebates, or cost adjustments in a delivery network.

## Features

* Directed weighted graph representation
* Supports positive and negative edge weights
* Bellman-Ford shortest path algorithm
* Early stopping when no further relaxation is possible
* Distance and parent table
* Shortest route reconstruction
* Unreachable vertex detection
* Reachable negative-cycle detection
* Identifies vertices affected by a negative cycle
* Performance analysis
* Built-in test cases for different graph conditions
* Interactive menu-driven interface

## Algorithm

The program follows these steps:

1. Store all directed edges.
2. Initialize the source distance to `0`.
3. Initialize all other distances to infinity.
4. Relax every edge up to `V - 1` times.
5. Stop early if no distance is updated during a pass.
6. Perform one additional pass to detect a reachable negative cycle.
7. Mark vertices affected by a negative cycle.
8. Reconstruct shortest routes only when a finite shortest path exists.

## Time and Space Complexity

**Time Complexity:** `O(V × E)`

**Space Complexity:** `O(V + E)`

Where:

* `V` = number of vertices
* `E` = number of edges

## Test Cases

The program includes five built-in test cases:

| Test Case | Condition                      | Expected Result                                |
| --------- | ------------------------------ | ---------------------------------------------- |
| 1         | Positive edge weights          | Shortest route is found                        |
| 2         | Negative edges without a cycle | Shortest route with negative cost is found     |
| 3         | Unreachable vertex             | Vertex is reported as unreachable              |
| 4         | Reachable negative cycle       | No finite shortest path is reported            |
| 5         | Unreachable negative cycle     | Negative cycle is not reported from the source |

## Project Structure

```text
delivery-route-planner/
├── src/
│   └── main.c
├── README.md
└── .gitignore
```

## Compilation

Compile the program using GCC:

```bash
gcc src/main.c -o route_planner
```

## Run

### Windows PowerShell

```powershell
.\route_planner.exe
```

### Linux / macOS

```bash
./route_planner
```

## Example

For a graph containing:

```text
0 → 1 (4)
0 → 2 (1)
2 → 1 (2)
1 → 3 (1)
2 → 3 (5)
```

The shortest route from vertex `0` to vertex `3` is:

```text
0 → 2 → 1 → 3
```

with total cost:

```text
4
```

## Technologies Used

* C
* GCC
* Bellman-Ford Algorithm
* Data Structures and Algorithms

## Academic Project

This project was developed as an individual academic mini-project for the **Analysis of Algorithms** course, focusing on shortest-path computation using the Bellman-Ford algorithm.
