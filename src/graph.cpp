#include "graph.h"

Graph::Graph(string airportFileName, string routeFileName) {
    //Parse the data
    string airport;
    string route;

    std::ifstream airportFile(airportFileName);
    std::ifstream routeFile(routeFileName);

    //Hash map of airports and their latitude/longitude coordinates for edge weights later
    unordered_map<Vertex, std::pair<double, double>> coordinates;

    while(getline(airportFile, airport)) {
        vector<string> info = split(airport, ',');
        string source = info.back();
        string type = info[info.size() - 2];
        if(source != "\"OurAirports\"" or type != "\"airport\"") continue;
        string IATA = info[4];
        insertVertex(IATA);
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

        if(coordinates.find(IATA) == coordinates.end()) //This Airport has not been saved in our hastable yet
                coordinates[IATA] = {latitude, longitude};
    }

    while(getline(routeFile, route)) {
        vector<string> info = split(route, ',');
        string source = info[2];
        string destination = info[4];

        //From the airport text file, each IATA code is surrounded with double quotes.
        //This is not the case with the route file. The two lines below corrects this mistake.
        string correctedSource = "\"" + source + "\"";
        string correctedDestination = "\"" + destination + "\"";

        std::pair<double, double> sourceCoords = coordinates[correctedSource];
        std::pair<double, double> destCoords = coordinates[correctedDestination];
        double distance = haversine(sourceCoords.first, sourceCoords.second, destCoords.first, destCoords.second);
        insertEdge(source, destination, distance);
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
    if(edgeExists(source, destination)) return false;

    //Source vertex does not exist in adjacency list
    if(!vertexExists(source)) adjacency_list[source] = unordered_map<Vertex, Edge>();
    //Insert edge
    adjacency_list[source][destination] = Edge(source, destination, weight);

    //Source vertex does not exist in adjacency list
    if(!vertexExists(destination)) adjacency_list[destination] = unordered_map<Vertex, Edge>();
    //Insert edge
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


int Graph::shortestPathLength(Vertex source, Vertex destination) {
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