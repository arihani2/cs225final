#include "graph.h"

Graph::Graph(std::string airportsFile, std::string flightsFile) {
    //Parse the data
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

int Graph::getEdgeWeight(Vertex source, Vertex destination) const {
    if(!assertEdgeExists(source, destination)) return -1;
    return adjacency_list[source][destination].getDistance();
}

void Graph::insertVertex(Vertex v) {
    // will overwrite if old stuff was there
    // removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}

bool Graph::insertEdge(Vertex source, Vertex destination) {
    if(edgeExists(source, destination)) return false;

    //Source vertex does not exist in adjacency list
    if(!vertexExists(source)) adjacency_list[source] = unordered_map<Vertex, Edge>();
    //Insert edge
    adjacency_list[source][destination] = Edge(source, destination);

    //Source vertex does not exist in adjacency list
    if(!vertexExists(destination)) adjacency_list[destination] = unordered_map<Vertex, Edge>();
    //Insert edge
    adjacency_list[destination][source] = Edge(source, destination);
    
    return true;
}

//TODO: fix this function. Does not actually change the weight
//Might not even need this tbh, planning on implementing an edge constructor that sets the weight
Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight) {
    if(!edgeExists(source, destination)) return Edge();

    //Old edge
    Edge e = adjacency_list[source][destination];

    //New edge src->dest
    Edge new_edge(source, destination);
    adjacency_list[source][destination] = new_edge;

    //New edge dest -> src
    Edge new_edge_reverse(destination,source);
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