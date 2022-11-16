## Leading Question 
Given a dataset of airport information, we would like to create a tool to find the path between airport A and airport B which would minimize the number of connections. We would also want to find the quickest flights out of the flights with the least number of connections. We would also like to know what airport sees the most connecting flights. To answer these questions we will implement a shortest path algorithm, as well as analyzing the betweenness centrality of the graph. For the shortest path algorithm, we will implement Djikstra’s Algorithm to find the shortest path between two airports. To analyze the betweenness centrality of the graph, we will implement the Floyd-Warshall algorithm. To compare the shortest number of connecting flights versus the shortest distance path, we will implement a Breadth First Search (BFS) algorithm for our graph and treat the graph as unweighted. The weights for the graph will be the distance between the airports.

## Dataset Acquisition
We will be using the OpenFlights dataset for this project.
Direct Link to the Dataset:
https://openflights.org/data.html

## Data Format
The OpenFlights website has multiple datasets. Our nodeset is the airport database. The airport database is a CSV file with each airport in the database listed on its own line in the following format:
Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST Database Time Zone, Type, Source. 
Our edgeset is the Route Database. The route database is a CSV file that lists a route between two airports in the following format:
Airline, Airline ID, Source Airport, Source Airport ID, Destination Airport, Destination Airport ID, Codeshare, Stops, Equipment.
The airport database has about 14110 nodes and the route database has about 67663 routes. Since this dataset is relatively small we plan on using the entire dataset.

## Data Correction
We will parse the input using an ifstream and add the data to our structure. For airports, we will only be needing the Airport ID, Name, Latitude, Longitude. For flights we will only be needing Source Airport, Source Airport ID, Destination Airport, Destination Airport ID, Stops. When processing our data, we will filter out any node that does not have type “airport” to ensure we are not adding nodes for ports or stations. We will also filter out any airport that is not of a valid source (any legacy data or user imported data). We will check for errors by checking to make sure that for each flight, that both airports exist (i.e. there are no edges that point to or from a node that is not in the data set). We can also check to ensure that there are no self loops, since no airport should have a flight flying back to itself. Similarly, there should be no airports with zero flights leaving or landing, otherwise the airport shouldn’t need to exist. If we encounter a flight which should not exist, we will simply not add it to the graph. At the end we can remove any island airports by looping over the vertices in our adjacency set. Since multiple airlines can have flights to and from the same airports, we will make sure to only add one instance of that edge by using the adjacency set. 


## Data Storage
We will be coding our own adjacency set data structure to store vertices (airports) and edges (flights).We will also be using disjoint sets to query whether an airport is connected at all to another airport, and we can also use this data structure to count the number of connected groups of airports. To find the shortest path from airport A to airport B, we will use Dijkstra’s Algorithm, and the data structure that is optimal for this algorithm in terms of runtime and space is the disjoint sets and adjacency set. Since we will need to store both nodes and edges, and each edge should theoretically be bi-directional (undirected graph), the space complexity will be O(n^2) where n is the number of airports in the dataset. The maximum number of possible edges for each node will be (n-1). Thus, the storage complexity in our adjacency set will be O(n*(n-1)) which is O(n^2).

## Algorithm 
Algorithm 1: BFS
Algorithm 2: Dijkstra’s shortest path
Algorithm 3: Betweenness Centrality/Floyd-Warshall Algorithm

We will use Dijkstra’s Shortest Path Algorithm to determine the shortest path between airports A and B. The weights that will be used by the algorithm is the distance between the airports. We will implement the BFS to determine the least amount of connections needed between two airports. To determine the betweenness centrality aspect of the graph, we will implement the Floyd-Warshall Algorithm.

Functions: There will be a function outputting the minimum number of connections from airport A and B. There will be another function using the previous function to output the recommended shortest path from airport A to airport B, tiebreaking by shortest distance. There will also be a function which can output a boolean representing there exists a path from airport A to B. Since we will be using Dijkstra’s Algorithm, our target runtime will be O((n+m)log(n)). There will be a function that does the Floyd-Warshall Algorithm on our graph. The runtime for this function will be O(n^3) where n is the number of nodes, which is not ideal. Lastly, there will be a function traversing the entire graph of airports and outputting the airport which is used the most as a connecting flight or destination. This airport will be the airport which is used the most often as a connection in shortest path calculations.


## Timeline
Week 1 Data Acquisition(11/11): implement the adjacency set class and set up ifstream to parse all data.
Week 2 Data Processing(11/18): begin parsing data and create adjacency set using this data.
Week 3 Algorithm Development(12/2): perform BFS and Dijkstra’s algorithm generating shortest paths. Use this and coordinate positions to finish min number of connections functions and recommended shortest path function
Week 4 betweenness centrality (12/8): utilize Floyd-Warshall Algorithm to calculate the most accessible airport, that is the airport that is most commonly used as a connection or destination.

