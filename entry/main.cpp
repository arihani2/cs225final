#include <iostream>
#include "../src/graph.h"

int main() {
    Graph test("../data/airport.txt", "../data/route.txt");
    //std::cout << test.getEdgeWeight("ORD", "LAX") << std::endl;
    std::cout << test.shortestPathLength("ORD", "LAX") << std::endl; //Chicago to LA --> 1
    std::cout << test.shortestPathLength("CMI", "LAX") << std::endl; //Champaign to LA --> 2
    std::cout << test.shortestPathLength("SFO", "LAX") << std::endl; // San Fran to LA --> 1
    std::cout << test.shortestPathLength("CMI", "ICN") << std::endl; // Champaign to Seoul --> 2
    std::cout << test.shortestPathLength("CMI", "GMP") << std::endl; // Champaign to Gimpo (regional korean airport) --> 3
    
    return 0;
}