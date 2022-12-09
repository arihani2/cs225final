#include <iostream>
#include "../src/graph.h"

int main() {
    Graph test("../data/airport.txt", "../data/route.txt");
    //std::cout << test.getEdgeWeight("ORD", "LAX") << std::endl;

    /*
    std::cout << test.minNumConnections("ORD", "LAX") << std::endl; //Chicago to LA --> 1
    std::cout << test.minNumConnections("CMI", "LAX") << std::endl; //Champaign to LA --> 2
    std::cout << test.minNumConnections("SFO", "LAX") << std::endl; // San Fran to LA --> 1
    std::cout << test.minNumConnections("CMI", "ICN") << std::endl; // Champaign to Seoul --> 2
    std::cout << test.minNumConnections("CMI", "GMP") << std::endl; // Champaign to Gimpo (regional korean airport) --> 3
    std::cout << test.minNumConnections("BRR", "CMI") << std::endl;
    std::cout << test.minNumConnections("DEC", "BRR") << std::endl;
    std::cout << test.minNumConnections("SFO", "SFO") << std::endl;
    */

   //std::cout << test.minNumConnections("ORD", "LAX") << std::endl;
   std::cout << test.shortestPathLength("ORD", "SFO") << std::endl;
   //std::cout << test.shortestPathLength("CMI", "SFO") << std::endl;
    
    
    
    return 0;
}