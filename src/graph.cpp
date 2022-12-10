#include "graph.h"

Graph::Graph(string airportFileName, string routeFileName) {
    //Parse the data
    string airport;
    string route;

    std::ifstream airportFile(airportFileName);
    std::ifstream routeFile(routeFileName);

    //Hash map of airports and their latitude/longitude coordinates for edge weights later
    unordered_map<Vertex, std::pair<double, double>> coordinates;
    //A list of all vertices to loop through in cleansing stage
    vector<Vertex> allVertices;

    while(getline(airportFile, airport)) {
        vector<string> info = split(airport, ',');
        string source = info.back();
        string type = info[info.size() - 2];
        if(source != "\"OurAirports\"" or type != "\"airport\"") continue;
        string IATA = info[4];

        //IATA code is wrapped in double quotes, this gets rid of that for ease
        string correctedIATA = IATA.substr(1,3);
        insertVertex(correctedIATA);
        allVertices.push_back(correctedIATA);
        double latitude;
        double longitude;

        //This is the expected input size with no extraneous commas in the aiport name
        if(info.size() == 14) {
            latitude = stod(info[6]);
            longitude = stod(info[7]);
        } else {
            //This deals with the case that there is an extra comma in the airport name, causing an extra entry
            //in the input vector.
            latitude = stod(info[7]);
            longitude = stod(info[8]);
        }

        if(coordinates.find(correctedIATA) == coordinates.end()) //This Airport has not been saved in our hastable yet
                coordinates[correctedIATA] = {latitude, longitude};
    }

    while(getline(routeFile, route)) {
        vector<string> info = split(route, ',');
        string source = info[2];
        string destination = info[4];

        std::pair<double, double> sourceCoords = coordinates[source];
        std::pair<double, double> destCoords = coordinates[destination];
        double distance = haversine(sourceCoords.first, sourceCoords.second, destCoords.first, destCoords.second);
        insertEdge(source, destination, distance);
    }

    //This does the majority of our data cleansing.
    clean(allVertices);
}

void Graph::clean(vector<Vertex>& vec) {
    for(Vertex airport: vec) {
        if(edgeExists(airport, airport)) adjacency_list[airport].erase(airport); //Remove self loop
        if(getAdjacent(airport).empty()) adjacency_list.erase(airport); //Remove airport with no edges
    }
}

vector<Vertex> Graph::getAdjacent(Vertex source) const {
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end()) return vector<Vertex>();
    else {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge>& map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++) {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}

Edge Graph::getEdge(Vertex source , Vertex destination) const {
    if(!assertEdgeExists(source, destination)) return Edge();
    return adjacency_list[source][destination];
}

bool Graph::vertexExists(Vertex v) const {
    return assertVertexExists(v);
}

bool Graph::edgeExists(Vertex source, Vertex destination) const {
    return assertEdgeExists(source, destination);
}

double Graph::getEdgeWeight(Vertex source, Vertex destination) const {
    if(!assertEdgeExists(source, destination)) return -1;
    return adjacency_list[source][destination].getDistance();
}

void Graph::insertVertex(Vertex v) {
    // will overwrite if old stuff was there
    // removeVertex(v);
    if(vertexExists(v)) return;
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}

bool Graph::insertEdge(Vertex source, Vertex destination, double weight) {
    //Edge already exists
    if(edgeExists(source, destination)) return false;

    //Data correction step
    //If the source airport or destination airport is not in our database, do not add the edge.
    if(!vertexExists(source) or !vertexExists(destination)) return false;

    //Insert edges
    adjacency_list[source][destination] = Edge(source, destination, weight);
    adjacency_list[destination][source] = Edge(source, destination, weight);
    
    return true;
}

//Might not even need this tbh, planning on implementing an edge constructor that sets the weight
//If using this might not need the Edge return. Won't need it most likely.
Edge Graph::setEdgeWeight(Vertex source, Vertex destination, double weight) {
    if(!edgeExists(source, destination)) return Edge();

    //Old edge
    Edge e = adjacency_list[source][destination];
    if(e.getDistance() == weight) return Edge(); //If original edge weight is the same as the new

    //New edge src->dest
    Edge new_edge(source, destination, weight);
    adjacency_list[source][destination] = new_edge;

    //New edge dest -> src
    Edge new_edge_reverse(destination,source, weight);
    adjacency_list[destination][source] = new_edge_reverse;

    return new_edge;
}


bool Graph::assertVertexExists(Vertex v) const {
    return adjacency_list.find(v) != adjacency_list.end();
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination) const {
    //The source vertex does not exist in the adjacency list
    auto findSource = adjacency_list.find(source);
    if(findSource == adjacency_list.end()) return false;

    //The destination vertex does not exist in the edge list of the source vertex
    unordered_map<Vertex, Edge>& edgeList = adjacency_list[source];
    auto findDestination = edgeList.find(destination);
    if(findDestination == edgeList.end()) return false;

    //Edge between the two vertices exists
    return true;
}

void Graph::clear() {
    adjacency_list.clear();
}

vector<string> Graph::split(string word, char del) {
    vector<string> to_return;

    std::stringstream ss(word);
    string to_add;
    while (!ss.eof()) {
        getline(ss, to_add, del);
        to_return.push_back(to_add);
    }

    return to_return;
}

double Graph::haversine(double latitude1, double longitude1, double latitude2, double longitude2) {
    //Convert latitude and longitude to radians
    double lat1 = latitude1 * M_PI / 180;
    double lon1 = longitude1 * M_PI / 180;
    double lat2 = latitude2 * M_PI / 180;
    double lon2 = longitude2 * M_PI / 180;

    //Find change in latitude and longitude
    double deltaLat = lat2-lat1;
    double deltaLon = lon2-lon1;

    //Apply formula
    double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat1) * cos(lat2) * sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = RADIUS * c;

    return round(d * 100) / 100; //This rounds the distance to the hundredth km.
}


/**
 * Prints the graph to stdout.
 */
// void Graph::print() const
// {
//     for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
//     {
//         cout << it->first << endl;
//         for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
//         {
//             std::stringstream ss;
//             ss << it2->first; 
//             string vertexColumn = "    => " + ss.str();
//             vertexColumn += " " ;
//             cout << std::left << std::setw(26) << vertexColumn;
//             string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
//             cout << std::left << std::setw(26) << edgeColumn;
//             if (weighted)
//                 cout << "weight = " << it2->second.getWeight();
//             cout << endl;
//         }
//         cout << endl;
//     }
// }


int Graph::minNumConnections(Vertex source, Vertex destination) {
    // if the source and destination are the same, the shortest path is 0
    if (source == destination) {
        return 0;
    }

    // distances map stores the distance of each vertex from the source vertex
    map<Vertex, int> distances;

    // if BFS returns false, then the two airports are not connected
    if (!BFS(source, destination, adjacency_list.size(), distances)) {
        return -1;
    }

    // return the distance
    return distances[destination];
}

bool Graph::BFS(Vertex source, Vertex destination, int size, map<Vertex, int> &dist) {

    queue<Vertex> queue;

    map<Vertex, bool> visited;

    for (auto element : adjacency_list) {
        Vertex curr = element.first;
        visited[curr] = false;
        dist[curr] = INT_MAX;
    }

    visited[source] = true;
    dist[source] = 0;
    queue.push(source);

    // standard BFS algorithm:
    while (!queue.empty()) {
        Vertex temp = queue.front();
        queue.pop();
        for (auto element : adjacency_list[temp]) {
            Vertex curr = element.first;
            if (!visited[curr]) {
                visited[curr] = true;
                dist[curr] = dist[temp] + 1;
                queue.push(curr);

                // stop BFS algorithm when we arrive at destination.
                if (curr == destination) {
                    return true;
                }
            }
        }
    }
    return false;
}

Vertex Graph::minDistance(unordered_map<Vertex, double> &dist, unordered_map<Vertex, bool> &seen) {
    double min = DBL_MAX;
    Vertex min_vertex;
    
    for (auto& element : adjacency_list) {
        Vertex curr = element.first;
        if (seen[curr] == false && dist[curr] <= min) {
            min = dist[curr];
            min_vertex = curr;
        }
    }
    return min_vertex;
}

void Graph::dijkstra(Vertex src, unordered_map<Vertex, double> &dist) {
    unordered_map<Vertex, bool> sptSet;
    for (auto& element : adjacency_list) {
        Vertex curr = element.first;
        dist[curr] = DBL_MAX;
        sptSet[curr] = false;
    }
    dist[src] = 0;

    std::cout << adjacency_list.size() << std::endl;
    for (size_t count = 0; count < adjacency_list.size() - 1; count++) {
        Vertex u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (auto& element : adjacency_list) {
            Vertex v = element.first;
            if (sptSet[v] == false && u != v && edgeExists(u, v) && dist[u] != DBL_MAX && dist[u] + getEdgeWeight(u, v) < dist[v]) {
                dist[v] = dist[u] + getEdgeWeight(u, v);
            }
        }
        std::cout << count << std::endl;
    }
}

unordered_map<Vertex, double> Graph::shortestPathLength(Vertex src) {
    unordered_map<Vertex, double> distances;
    dijkstra(src, distances);
    return distances;
}