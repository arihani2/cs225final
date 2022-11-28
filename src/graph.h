/**
 * @file graph.h
 *
 * Update 11/16/2022
 * CS 225 Final Project Graph Class
 */
#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>

#include "edge.h"

using std::vector;
using std::string;
using std::to_string;
using std::unordered_map;


/**
 * Represents a graph; used by the GraphTools class.
 *
 */
class Graph {
    public:
        /**
         * Constructor taking in the file containing all airports and file containing all flights.
         */
        Graph(string airportFileName, string routeFileName);

        /**
         * Gets all adjacent vertices to the parameter vertex.
         * @param source - vertex to get neighbors from
         * @return a vector of vertices
         */
        vector<Vertex> getAdjacent(Vertex source) const;
        
        /**
         * Gets an edge between two vertices.
         * @param source - one vertex the edge is connected to
         * @param destination - the other vertex the edge is connected to
         * @return - if exist, return the corresponding edge
         *         - if edge doesn't exist, return Edge()
         */
        Edge getEdge(Vertex source, Vertex destination) const;

        /**
         * Checks if the given vertex exists.
         * @return - if Vertex exists, true
         *         - if Vertex doesn't exist, return false
         */
        bool vertexExists (Vertex v) const;

        /**
         * Checks if edge exists between two vertices exists.
         * @return - if Edge exists, true
         *         - if Edge doesn't exist, return false
         */
        bool edgeExists(Vertex source, Vertex destination) const;

        /**
         * Gets the weight of the edge between two vertices.
         * @param source - one vertex the edge is connected to
         * @param destination - the other vertex the edge is connected to
         * @return - if edge exists, return edge wright
         *         - if doesn't, return InvalidWeight
         */
        double getEdgeWeight(Vertex source, Vertex destination) const;

        /**
         * Inserts a new vertex into the graph and initializes its label as "".
         * @param v - the name for the vertex
         */
        void insertVertex(Vertex v);


        /**
         * Inserts an edge between two vertices.
         * A boolean is returned for use with the random graph generation.
         * Hence, an error is not thrown when it fails to insert an edge.
         * @param source - one vertex the edge is connected to
         * @param destination - the other vertex the edge is connected to
         * @return whether inserting the edge was successful
         */
        bool insertEdge(Vertex source, Vertex destination, double weight);

        /**
         * Sets the weight of the edge between two vertices.
         * @param source - one vertex the edge is connected to
         * @param destination - the other vertex the edge is connected to
         * @param weight - the weight to set to the edge
         * @return - if edge exists, set edge weight and return  edge with new weight
         *         - if not, return InvalidEdge
         */
        Edge setEdgeWeight(Vertex source, Vertex destination, double weight);

        void clear();

    private:
        mutable unordered_map<Vertex, unordered_map<Vertex, Edge>> adjacency_list;

        /**
         * Returns whether a given vertex exists in the graph.
         * @param v - the vertex to check
         * @param functionName - the name of the calling function to return
         *  in the event of an error
         */
        bool assertVertexExists(Vertex v) const;

        /**
         * Returns whether thee edge exists in the graph.
         * @param source - one vertex
         * @param destination - another vertex
         * @param functionName - the name of the calling function to return
         *  in the event of an error
         */
        bool assertEdgeExists(Vertex source, Vertex destination) const;

        vector<string> split(string word, char del);

        double haversine(double latitude1, double longitude1, double latitude2, double longitude2);

        const double RADIUS = 6371; //Mean radius of the Earth in KM

};