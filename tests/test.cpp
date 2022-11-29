#include <catch2/catch_test_macros.hpp>

#include "graph.h"
#include "edge.h"
#include "../src/graph.h"
#include "../src/edge.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Graph graph("../tests/airport.txt", "../tests/route.txt");

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

TEST_CASE("getEdgeWeight1", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE((graph.getEdgeWeight("ORD", "DEC") <= 252 and graph.getEdgeWeight("ORD", "DEC") >= 250));
}

TEST_CASE("getEdgeWeight2", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE((graph.getEdgeWeight("VCE", "CGN") <= 710 and graph.getEdgeWeight("VCE", "CGN") >= 708));
}

TEST_CASE("getEdgeWeight3", "[weight=1]" "[getEdgeWeight]") {
    REQUIRE(graph.getEdgeWeight("VCE", "ORD") == -1);
}

TEST_CASE("edgeExists1" , "[weight=1]" "[edgeExists]") {
    REQUIRE(graph.edgeExists("ORD", "JFK"));
}

TEST_CASE("edgeExists2" , "[weight=1]" "[edgeExists]") {
    REQUIRE(graph.edgeExists("ATL", "CUN"));
}

TEST_CASE("edgeExists3" , "[weight=1]" "[edgeExists]") {
    REQUIRE(!(graph.edgeExists("IKA", "ORD")));
}

//Insert Vertex
TEST_CASE("insertVertex1", "[weight=1]" "[insertVertex]") {
    REQUIRE(!(graph.vertexExists("LOL")));
    graph.insertVertex("LOL");
    REQUIRE(graph.vertexExists("LOL"));
}

TEST_CASE("insertVertex2", "[weight=1]" "[insertVertex]") {
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