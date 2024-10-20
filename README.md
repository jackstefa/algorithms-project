# Algorithms Project (2021)
## Project Description

The goal of this project is to manage a leaderboard of weighted directed graphs. The leaderboard tracks the top `k` "best" graphs based on a specific metric, and the program processes a sequence of commands provided via input.

### Input
1. Two parameters on the first line of input (space-separated):
   - `d`: the number of nodes in each graph.
   - `k`: the length of the leaderboard.
   
2. A sequence of commands:
   - `AggiungiGrafo [adjacency_matrix]`: Adds a graph to the set of graphs under consideration. The adjacency matrix is provided as a set of rows, with elements separated by commas.
   - `TopK`: Outputs the indices of the top `k` graphs with the smallest values according to the following metric:

### Metric
- For each graph, the metric is the sum of the shortest paths from node `0` to all other reachable nodes. If a node is unreachable, its distance is considered zero.
- In the case of a tie, the graphs are ranked by the order in which they were added.

### Output
- For the `TopK` command, the program prints the indices of the `k` graphs with the lowest metric values, separated by a space.
