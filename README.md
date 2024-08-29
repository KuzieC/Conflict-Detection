# Fast Route Conflict Detection Method Based on Space Box

## Project Overview

This project implements a fast and efficient route conflict detection method tailored for air traffic management. The method is based on spatial division, where the airspace is segmented into smaller units called "space boxes." By predicting the movement of aircraft within these space boxes, potential conflicts are detected early, allowing for timely interventions. This approach reduces computational complexity and is highly suitable for large-scale, real-time applications.

## Key Features

- **Spatial Division**: The airspace is divided into overlapping rectangular space boxes to ensure all potential conflicts, especially those near boundaries, are detected.
- **Predictive Conflict Detection**: The algorithm predicts the future positions of aircraft based on current trajectories and checks for conflicts within the same space box.
- **Low Complexity**: The method significantly reduces the number of necessary computations, making it faster and more efficient than traditional methods.
- **Parallel Processing Ready**: The algorithm is designed to be easily parallelizable, making it ideal for real-time large-scale applications.

## Methodology

### Coordinate System

- The airspace coordinates are converted from a geodetic coordinate system to a rectangular coordinate system for easier calculation of spatial relationships.

### Space Box Division

- The airspace is divided into rectangular units called space boxes. Each space box is defined by its center coordinates and dimensions (length, width, height).
- Space boxes overlap to ensure that any potential conflicts near the edges are captured.

### Conflict Detection

1. **Track Calculation**: The position of each aircraft is projected based on its current heading and speed.
2. **Space Box Assignment**: Each aircraft is assigned to a space box based on its coordinates.
3. **Distance Calculation**: If multiple aircraft are found in the same space box, the algorithm calculates the distance between them over time.
4. **Conflict Prediction**: If the distance between two aircraft is decreasing, a conflict is predicted, and an alert is generated.

### Algorithm Complexity

- The algorithm's complexity is \( O(28m + mn) \), where \( m \) is the number of routes, and \( n \) is the number of prediction steps. This is significantly more efficient compared to traditional methods.

## File Explanations

### Python File: `main.py`

- **Purpose**: This script simulates the movement of a specified number of aircraft within a defined airspace. It checks for potential collisions based on the positions and directions of the aircraft, divided into units within the airspace.

- **Key Features**:
  - **Random Initialization**: Aircraft are assigned random positions and velocities within the airspace.
  - **Collision Detection**: The script iterates through each time step, updating aircraft positions and checking for potential conflicts within the same unit.
  - **Performance Measurement**: The script calculates the average time taken for each simulation step, which helps in understanding the efficiency of the conflict detection algorithm.

- **Visualization**: The `plot.py` script can be used to visualize the positions and movements of the aircraft.

### C++ File: `main.cpp`

- **Purpose**: This C++ program provides a more performance-oriented implementation of the conflict detection algorithm. It is optimized for speed and efficiency, making it suitable for real-time applications.

- **Key Features**:
  - **High-Resolution Timing**: The program uses Windows-specific functions to measure the time taken for each simulation step, offering precise performance metrics.
  - **Spatial Division**: Similar to the Python script, the airspace is divided into units, and aircraft are assigned to these units based on their positions.
  - **Conflict Detection**: The algorithm checks for potential collisions within each unit, ensuring that conflicts are identified efficiently.

- **Performance**: The program outputs the average time taken to detect conflicts, providing insights into the algorithm's real-time performance.

### Utility File: `time.cpp`

- **Purpose**: This file demonstrates the use of high-resolution timers in C++ for measuring the performance of the conflict detection algorithm.

- **Key Features**:
  - **Timer Macros**: It defines macros for initializing, starting, and stopping the timer, which can be used in various parts of the C++ code.
  - **Sample Usage**: A basic example is provided to illustrate how to measure elapsed time for a specific task.

### Visualization File: `plot.py`

- **Purpose**: This Python script is used to visualize the aircraft positions and any potential conflicts detected by the algorithm.

- **Key Features**:
  - **Scatter Plot**: The script creates a scatter plot to show the positions of aircraft within the airspace.
  - **Conflict Highlighting**: Aircraft involved in potential conflicts are highlighted, providing a clear visual indication of where and when conflicts occur.

## Simulation and Performance

The simulation was conducted over a control area of 1000 km by 1000 km with a height of 30 km, divided into space boxes of 20 km by 20 km by 1 km. The results demonstrated that as the number of aircraft increased, the algorithm's time efficiency improved significantly compared to other methods.

### Experiment Results

| Tracks | Literature [16] Time (ms) | Literature [17] Time (ms) | This Algorithm Time (ms) |
|--------|---------------------------|---------------------------|--------------------------|
| 10     | 15                        | 7                         | 1.071                    |
| 50     | 383                       | 164                       | 1.224                    |
| 100    | 1542                      | 651                       | 1.453                    |
| 200    | 6244                      | 2224                      | 1.608                    |

## Conclusion

This project presents a highly efficient and scalable method for detecting route conflicts in air traffic management. By focusing on spatial division and predictive modeling within defined space boxes, the algorithm achieves significant improvements in computation time and scalability. It is particularly well-suited for large-scale, real-time applications in dynamic airspaces.

## References

For a detailed list of references and further reading, please refer to the original document.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact

For any questions or collaboration opportunities, please contact Guanzhi Chen at [email@example.com](mailto:email@example.com).
