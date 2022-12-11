# CS 225 Final Report
## Algorithm Overview
### Dijkstra’s
Our implementation of Dijkstra's Algorithm takes a starting airport (the three digit IATA code), and a hash map, and modifies the hash map with the pairings of ending vertices (also the three digit IATA code) and their respective distances following the shortest weighted path. Our implementation is not optimal and runs in O(V^2), where V is the number of vertices in the graph. 

To test Dijkstra's algorithm, we wrote multiple test cases for aiport distances that we know and required that the hash map pairings are within 1 kilometer of this known distance (due to rounding errors).

### Betweenness Centrality/Brande's Algorithm
Our Brande's Algorithm implementation is a modified version of our originally planned Floyd-Warshall's Algorithm. It takes in no inputs, and outputs the airport that sees the most connecting flights from all shortest paths. The airport that we found had the most connecting flights was Governor André Franco Montoro International Airport (IATA Code GRU) based in Guarulhos, Brazil.

To ensure that our algorithm is correct, we created tests using airports that we know the betweenness centrality of and confirmed that the algorithm outputs a correct result for that airport using a helper function.

### Breadth-First Search
Our breadth-first search algorithm takes in a starting node and an ending node and outputs the number of connecting flights between the two aiports, ignoring weight (a return of 0 means direct flight). Since the dataset is so massive and that since there can exists many paths of the same length between any two airports, we only output the number of connecting flights and not the actual path between the starting and ending nodes.

We confirmed that the traversal is working as intended by adding test cases with results we can manually confirm (i.e. direct flights, nodes with only one edge, etc.).

## Leading Question
By implementing our algorithms, we were not able to completely answer our leading question of the shortest weighted path between two airports, but we were able to answer our other leading questions of what the most connected airport is, and the minimum number of connections between two airports.

Our Dijkstra's algorithm was not implemented the way that we had originally planned. We had difficulty implementing the algorithm that produces the optimal run time, and due to the time constraint of the project, we opted to implement an easier version of the algorithm that runs slower, but still outputs a similar result. The algorithm only outputs the minimum distances between two airports, but does not output the path. If we had more time for this project, we would have liked to implement the algorithm as intended in the contract.

Our Betweenness Centrality algorithm that we implemented was also not the way that we had originally planned. We had planned to use Floyd-Warshall's algorithm to find this information, which would have ran in O(V^3) time. When we committed to writing this algorithm, we did not fully understand how massive the dataset actually is, and how long the algorithm would take to run. We opted to write Brande's Algorithm, a modified version of Floyd-Warshall's, instead to find our the most connected airport. Since our graph is unweighted, we chose Brande's Algorithm because this algorithm runs in O(V*E), which is significantly faster than Floyd-Warshall's, but ignores weight. If we had more time for this project, we would have liked to implement a betweeness centrality algorithm that incorporates the weight.

Ultimately, our project was semi-successful from what we originally sought. Dijkstra's algorithm did not adhere to our proposed run-time, and although we implemented a faster algorithm, we did not use the algorithm that incorporates the weight that we had originaly intended for betweeneess centrality. Our shortcomings came from a lack of communication and time. Unfortunatley, all our schedules made it very difficult to meet outside of our scheduled time, and as such most of the work was done remotely and this was the source of our miscommunications, which were hard to solve for the most part. When meeting in person, we worked great as a team and made heavy progress towards our goals, but outside of these meeting times was a different group. Ultimately, given another chance with less on our plate, we would have liked to meet more in person to work more productively together and create a better final product.