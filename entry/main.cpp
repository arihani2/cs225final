#include <iostream>
#include "../src/graph.h"

int main() {
    Graph test("../data/airport.txt", "../data/route.txt");
    std::cout << test.getEdgeWeight("ORD", "LAX") << std::endl;
    return 0;
}