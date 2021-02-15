#include "Graph.h"

int main() {
	std::ifstream file("mona_1000.txt");
	ui n;
	file >> n;
	Graph test(n, std::move(file));
	IteratedLocalSearch(test);
	std::cout << std::setprecision(15) << test.getSolutionWeight() << std::endl;
	test.print();
	file.close();
	return 0;
}
