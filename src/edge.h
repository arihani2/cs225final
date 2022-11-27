/**
 * @file edge.h
 * CS 225 Final Project Edge Class
 */

#pragma once

#include <string>

using std::string;

typedef string Vertex;

/**
 *
 * @author Matthew Lee
 * @date Fall 2022
 */

class Edge
{
  public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v)
        : source(u), dest(v), distance(0)
    { 
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param d - the distance of the edge
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, double d)
        : source(u), dest(v), distance(d)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(""), dest(""), distance(0)
    { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return distance < other.getDistance();
    }


    /**
     * Gets edge weight.
     */
    int getDistance() const
    {
        return this->distance;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }
private:
    double distance; /**< The edge weight (if in a weighed graph) **/

};
