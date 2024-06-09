"""
------------ PROBLEM 1 -----------
1) Initialization
The 'Maze' class is initialized with a file name. The maze is loaded from the file,
and the positions of robots are identified.

2) A* Search
- A* search algorithm is implemented in the 'a_star_search' method of the Maze
- The algorithm maintains a priority queue 'frontier' to explore paths based on their
estimated costs.
- Initially,the start node is added to the frontier with a cost of 0 and empty path.
- While there are nodes to explore in the frontier:
    - The node with the lowest estimated cost is selected and removed from the frontier.
    - If the selected code is the goal node, the algorithm returns the path leading to it
    - Otherwise, the node is marked as explored, and all its neighboring nodes are considered
    - For each valid neighbor, a new path is created by extending the current path.
    - The new path and its estimated cost are added to the frontier.
- If the goal node is not reached and the frontier becomes empty, the algorithm returns None

3) Heuristic Function
- The heuristic function used is the Manhattan Distance between two points
- In the 'manhattan_distance' method of the 'Maze' class, the Manhattan Distance is
calculated as the sum of the absolute differences in their x and y coordinates.
- This heuristic provides an admissible estimate of the remaining distance to the goal.

4) Calculating Shortest Distance Between Robots
- The 'shortest_distances_between_robots' method of the 'Maze' class calculates the
shortest distance between al pairs of robots in the maze.
- It iterates over all pairs of robots and uses the A* search to find the shortest path.
- If a path exists, its length minus one is considered the distance between the robots
- If no path exists, the distance is set to infinity
- The distances are stored in a dictionary where the keys are tuples of robot names and
the values are the corresponding distances

5) Printing Results
- The calculated distances between robots are printed in the given format
- The 'printed_edge' set is used to ensure that each edge is printed only once, and
the edges are sorted alphabetically by the names of the robots.
- Before printing each edge, it checks if the reversed edge has not been printed
to avoid duplicate output
"""

import heapq


class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)[1]


class Maze:
    def __init__(self, filename):
        self.grid = self.load_maze(filename)
        self.width = len(self.grid[0])
        self.height = len(self.grid)
        self.robots = {}
        self.find_robots()

    def load_maze(self, filename):
        # Load the maze from the specified file
        with open(filename, 'r') as f:
            return [[char for char in line.strip()] for line in f]

    def find_robots(self):
        # Find the positions of all robots in the maze
        for y in range(self.height):
            for x in range(self.width):
                if self.grid[y][x] in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
                    self.robots[self.grid[y][x]] = (x, y)

    def is_valid(self, x, y):
        # Check if the specified position is valid in the maze
        return 0 <= x < self.width and 0 <= y < self.height and self.grid[y][x] != '#'

    def manhattan_distance(self, start, goal):
        # Calculate the Manhattan distance between two points
        return abs(start[0] - goal[0]) + abs(start[1] - goal[1])

    def a_star_search(self, start, goal):
        frontier = []
        heapq.heappush(frontier, (0, [start]))
        explored = set()

        while frontier:
            current_cost, path = heapq.heappop(frontier)
            current_node = path[-1]

            if current_node == goal:
                return path

            if current_node in explored:
                continue

            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                next_x, next_y = current_node[0] + dx, current_node[1] + dy
                if self.is_valid(next_x, next_y):
                    new_path = path + [(next_x, next_y)]
                    new_cost = current_cost + 1
                    heuristic = new_cost + self.manhattan_distance((next_x, next_y), goal)

                    heapq.heappush(frontier, (heuristic, new_path))

            explored.add(current_node)

        return None

    def shortest_path(self, start_robot, goal_robot):
        # Find the shortest path between two robots in the maze
        if start_robot not in self.robots or goal_robot not in self.robots:
            return None

        start = self.robots[start_robot]
        goal = self.robots[goal_robot]
        path = self.a_star_search(start, goal)

        if path is None:
            return None

        return path

    def shortest_distances_between_robots(self):
        # Calculate the shortest distances between all pairs of robots in the maze
        distances = {}
        for robot1 in self.robots:
            for robot2 in self.robots:
                if robot1 != robot2:
                    distance = self.shortest_path(robot1, robot2)
                    if distance:
                        distances[(robot1, robot2)] = len(distance) - 1
                    else:
                        distances[(robot1, robot2)] = float('inf')
        return distances


class TSPSolver:
    def __init__(self, graph):
        self.graph = graph
        self.start_node = sorted(list(graph.keys()))[0] # Node A

    def ucs(self):
        frontier = [(0, self.start_node)]  # Initialize the frontier with node A and its cost
        explored = set()
        goal_nodes = set(self.graph.keys())  # Set of all nodes

        # Initialize answer vector to maximum value
        answer = {node: float('inf') for node in goal_nodes}

        # Count for number of goal nodes reached
        count = 0

        while frontier:
            # Sort the frontier based on cost
            frontier.sort(reverse=True)
            cost, node = frontier.pop()

            # Check if the current node is part of the goal nodes
            if node in goal_nodes:
                # Update the answer for the goal node if cost is lower
                if answer[node] > cost:
                    answer[node] = cost

                    # Increment count if a new goal node is reached
                    count += 1

                # If all goal nodes have been reached, return the answer
                if count == len(goal_nodes):
                    return answer

            # Explore neighbors of the current node
            if node not in explored:
                for neighbor, neighbor_cost in self.graph[node].items():
                    # Add neighbor to the frontier with updated cost
                    new_cost = cost + neighbor_cost
                    frontier.append((new_cost, neighbor))

                # Mark current node as explored
                explored.add(node)
        return answer

    def dfs(self, node, visited, path):
        """
            Perform depth-first search (DFS) to find a tour that visits all nodes once and returns to the starting node.

            Args:
                node (str): The current node being visited.
                visited (set): A set containing nodes that have been visited.
                path (list): A list containing the current path being explored.

            Returns:
                list or None: A list representing the tour if found, otherwise None.
            """

        # Check if all nodes have been visited exactly once
        if len(visited) == len(self.graph):
            return path

        # Iterate through neighbors of the current node
        for neighbor, neighbor_cost in self.graph[node].items():
            # Check if the neighbor has not been visited
            if neighbor not in visited:
                # Mark the neighbor as visited and append it to the current path
                visited.add(neighbor)
                path.append(neighbor)
                # Recursively explore the neighbor's neighbors
                result = self.dfs(neighbor, visited, path)
                # If a valid tour is found, return it
                if result:
                    return result
                # If no valid tour is found, backtrack by removing the neighbor from visited and the path
                visited.remove(neighbor)
                path.pop()

        # If no valid tour is found from this node, return None
        return None

    def solve_tsp_with_ucs(self):
        tour = self.ucs()
        if tour:
            # Sort the tour by node names and return the sorted tour
            sorted_tour = sorted(tour.items(), key=lambda x: x[0])
            return [node for node, _ in sorted_tour]
        else:
            return None

    def solve_tsp_with_dfs(self):
        # Initialize visited set with the starting node and path with the starting node
        visited = set([self.start_node])
        path = [self.start_node]
        # Start DFS from the starting node
        return self.dfs(self.start_node, visited, path)

# Create a maze object and calculate the shortest distances between robots
maze = Maze("maze.txt")
distances = maze.shortest_distances_between_robots()

printed_edges = set()  # Set to store printed edges

# Sort the distances dictionary by the names of the robots
sorted_distances = sorted(distances.items(), key=lambda x: (x[0][0], x[0][1]))

# Print the distances between robots in alphabetical order
print("\nShortest distance graph:")
for (robot1, robot2), distance in sorted_distances:
    if (robot2, robot1) not in printed_edges:  # Check if the reversed edge has not been printed
        print(f"{robot1},{robot2},{distance}")
        printed_edges.add((robot1, robot2))  # Add the printed edge to the set

# Construct the graph from the shortest distances
graph = {}
for (robot1, robot2), distance in distances.items():
    if robot1 not in graph:
        graph[robot1] = {}
    graph[robot1][robot2] = distance
    if robot2 not in graph:
        graph[robot2] = {}
    graph[robot2][robot1] = distance

# Solve the TSP using UCS
solver = TSPSolver(graph)
tour = solver.solve_tsp_with_ucs()
tour.append('A')
# Output the tour
print("\nTSP Tour with Uniform Cost:", tour)

tsp_solver_dfs = TSPSolver(graph)
tour = tsp_solver_dfs.solve_tsp_with_dfs()
tour.append('A')
print("\nTSP Tour with Depth First Search:", tour)
