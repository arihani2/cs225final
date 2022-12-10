#include <catch2/catch_test_macros.hpp>

#include "graph.h"
#include "edge.h"
#include "../src/graph.h"
#include "../src/edge.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//Create new graph
Graph graph("../tests/airport.txt", "../tests/route.txt");

//Check that random airports exist in the graph, and that airports with no connections are removed
TEST_CASE("vertexExists1", "[weight=1]" "[vertexExists]") {
    REQUIRE(graph.vertexExists("PPG"));
}

TEST_CASE("vertexExists2", "[weight=1]" "[vertexExists]") {
    REQUIRE(graph.vertexExists("THR"));
}

TEST_CASE("vertexExists3", "[weight=1]" "[vertexExists]") {
    REQUIRE(graph.vertexExists("BYC"));
}

TEST_CASE("vertexExists4", "[weight=1]" "[vertexExists]") {
    REQUIRE(graph.vertexExists("LUH"));
}

TEST_CASE("vertexExists5", "[weight=1]" "[vertexExists]") {
    REQUIRE(graph.vertexExists("CDC"));
}

TEST_CASE("vertexExists6", "[weight=1]" "[vertexExists]") {
    REQUIRE(!(graph.vertexExists("LOL")));
}

//Check that distances of a connecting flight are found correctly
// If no connection exists then -1 is returned
TEST_CASE("getEdgeWeight1", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE((graph.getEdgeWeight("ORD", "DEC") <= 252 and graph.getEdgeWeight("ORD", "DEC") >= 250));
}

TEST_CASE("getEdgeWeight2", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE((graph.getEdgeWeight("VCE", "CGN") <= 710 and graph.getEdgeWeight("VCE", "CGN") >= 708));
}

TEST_CASE("getEdgeWeight3", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE(graph.getEdgeWeight("VCE", "ORD") == -1);
}

// Check that returns two for to airports with connecting flight, false otherwise
TEST_CASE("edgeExists1" , "[weight=1]" "[edgeExists]") {
    REQUIRE(graph.edgeExists("ORD", "JFK"));
}

TEST_CASE("edgeExists2" , "[weight=1]" "[edgeExists]") {
    REQUIRE(graph.edgeExists("ATL", "CUN"));
}

TEST_CASE("edgeExists3" , "[weight=1]" "[edgeExists]") {
    REQUIRE(!(graph.edgeExists("IKA", "ORD")));
}

TEST_CASE("edgeExists4" , "[weight=1]" "[edgeExists]") {
    REQUIRE(!(graph.edgeExists("LOL", "ORD")));
}

//Insert Vertex
TEST_CASE("insertVertex_with_edge", "[weight=1]" "[insertVertex]") {
    graph.insertVertex("LOL");

    //checks that added vertex correctly
    REQUIRE(graph.vertexExists("LOL"));

    //checks that non existing edge is added
    REQUIRE(graph.insertEdge("LOL", "ORD", 1000));

    //checks that edge added "exists" and that getAdjacent works after adding
    REQUIRE(graph.edgeExists("LOL", "ORD"));
    REQUIRE(graph.edgeExists("ORD", "LOL")); 
    REQUIRE(graph.getAdjacent("LOL").size() == 1);
}

TEST_CASE("insertVertex1", "[weight=1]" "[insertVertex]") {
    graph.insertVertex("ORD");
    REQUIRE(graph.vertexExists("ORD"));
}

//Insert Edge
TEST_CASE("insertEdge1", "[weight=1]" "[insertEdge]") {
    REQUIRE(!(graph.insertEdge("ZZZ", "ZZY", 100)));
}

TEST_CASE("insertEdge2", "[weight=1]" "[insertEdge]") {
    int weight = graph.getEdgeWeight("ORD", "ANC");
    REQUIRE(!(graph.insertEdge("ORD", "ANC", weight)));
    REQUIRE(graph.edgeExists("ORD", "ANC"));
    REQUIRE(graph.edgeExists("ANC", "ORD"));
}

TEST_CASE("insertEdge3", "[weight=1]" "[insertEdge]") {
    REQUIRE(graph.insertEdge("LED", "TPA", 1000));
    REQUIRE(graph.edgeExists("LED", "TPA"));
    REQUIRE(graph.edgeExists("TPA", "LED"));
}

//getAdjacent
TEST_CASE("getAdjacent1", "[weight=1]" "[getAdjacent]") {
    vector<Vertex> adj = graph.getAdjacent("ORD");
    for (unsigned i = 0; i < adj.size(); i++) {
        REQUIRE(graph.getEdgeWeight("ORD", adj[i]) != -1);
    }
}

TEST_CASE("getAdjacent2" , "[weight=1]" "[getAdjacent]") {
     REQUIRE(graph.getAdjacent("ZZZ").size() == 0);
}

//Algorithm Testing
//BFS
TEST_CASE("BFS1", "[BFS]") {
    REQUIRE(graph.minNumConnections("ORD", "LAX")== 0); //Chicago to LA --> 1
}

TEST_CASE("BFS2", "[BFS]") {
    REQUIRE(graph.minNumConnections("CMI", "LAX")== 1); //Champaign to LA --> 2
}

TEST_CASE("BFS3", "[BFS]") {
    REQUIRE(graph.minNumConnections("SFO", "LAX")== 0); // San Fran to LA --> 1
}

TEST_CASE("BFS4", "[BFS]") {
    REQUIRE(graph.minNumConnections("CMI", "ICN")== 1); // Champaign to Seoul --> 2
}

TEST_CASE("BFS5", "[BFS]") {
    REQUIRE(graph.minNumConnections("CMI", "GMP")== 2); // Champaign to Gimpo (regional korean airport) --> 3
}

//Dijkstras Testing
TEST_CASE("Dijkstra1", "[Dijkstra]") {
    unordered_map<Vertex, double> distances = graph.shortestPathLength("CMI");
    REQUIRE(distances["ORD"] >= 217);
    REQUIRE(distances["ORD"] <= 219);
    REQUIRE(distances["SFO"] >= 3181);
    REQUIRE(distances["SFO"] <= 3182);
    REQUIRE(distances["DFW"] >= 1114);
    REQUIRE(distances["DFW"] <= 1116);
    REQUIRE(distances["ICN"] >= 9646);
    REQUIRE(distances["ICN"] <= 9648);
}


