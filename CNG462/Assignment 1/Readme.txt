Zeynep Naz Kaya - 2526481
Mert Can Bilgin - 2453025

This program implements A* Search, Uniform Cost Search (UCS), and Depth-First Search (DFS) algorithms to help Mr. Peace. The objective is to find the shortest tour to visit all the robots in a maze.

1. Compilation:
   - Run the main.py file with the maze.txt file provided.
   - Ensure that the maze.txt file is located in the same directory as main.py.

2. Input File Format (maze.txt):
   - The maze is provided in a text file named "maze.txt".
   - The maze should be represented using the following symbols:
        - '#' for walls
        - ' ' (space) for empty spaces
        - Characters 'A' to 'Z' (uppercase letters) for robots' positions

-------------------------------------------
          Program Functionality
-------------------------------------------

1. Maze Construction:
   - The maze layout is loaded from the maze.txt file.
   - Robots' positions are identified and represented in the maze.

2. Graph Construction:
   - A graph is constructed using the A* Search algorithm, considering the maze layout and robots' positions.

3. Shortest Tour Calculation:
   - UCS and DFS algorithms are used to find the shortest tour to visit all the robots in the maze for Mr. Peace.