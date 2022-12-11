# CS225 Final Project: Airports and Flights

<p align="center">
  <a href="#presentation-video">Presentation Video</a> •
  <a href="#data">Data</a> •
  <a href="#github-structure">Github Structure</a> •
  <a href="#running-instructions">Running Instructions</a> •
  <a href="#team-members">Team Members</a>
</p>

## [Presentation Video](https://youtu.be/Wmj5ifsMp44)

## Data

We are using the [OpenFlights Airports Database](https://openflights.org/data.html) data and focusing on the following two files:

- [OpenFlights airport dataset](airports.dat)
- [OpenFlights airport routes dataset](routes.dat)

## Github Structure

### Location of Major Files and Deliverables

- Our source code containing our classes and functions are located in the [src directory](https://github.com/arihani2/cs225final/tree/main/src). 

- Datasets are stored as txt files in the [`/data` directory](https://github.com/arihani2/cs225final/tree/main/data) directory.

- The Test cases and duplicate datasets are found in the [`/tests` directory](https://github.com/arihani2/cs225final/tree/main/tests).

- Project report, development log, contract, etc. are in [`/documents` directory](https://github.com/arihani2/cs225final/tree/main/documents). 

- The main.cpp file is located in the ['/entry' directory](https://github.com/arihani2/cs225final/tree/main/entry).


## Running Instructions 

To begin, we need to make sure [Docker](https://www.docker.com/) is running and a container is open.

### Building and Running the Executable

First, we need to create a build directory. Make sure you our in our project's main directory. Simply run `mkdir build` and then `cd build` to create and enter a build directory. Then run `cmake ..` to run CMake in the build directory. You are now ready to compile and run our code!

To use our program, run `make` then `./main` in the build directory.

1. BFS: 
   - Input: Airport Graph
   - Output: Minimum number of connections from source to destination airport
2. Dijkstra's:
   - Input: Airport Graph
   - Output: Shortest flight distance from source to destination airport
3. Modified Floyd Marshall's (Brandes algorithm):
   - Input: Airport Graph
   - Output: The betweenness centrality values for all airports

The path to the datasets from the entry directory in main.cpp is: `../data/filename.txt`

### Tests

To run the test cases, run `make test` then `./test` in the build directory.

We constructed test cases which utilized the enitre datasets. The data processing, graph implementation, and all algorithms were tested for all sorts of cases, including edge cases. Each function in the graph class contains several test cases.  

## Team Members

The Names and NetID of the contributors to this project:

- Anthony Rihani (`arihani2`)
- Matthew Lee (`ml95`)
- Darren Biskup (`biskup2`)
- Eduardo Martinez (`em18`)
