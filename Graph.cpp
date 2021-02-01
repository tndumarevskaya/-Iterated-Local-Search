#include "Graph.h"

double Graph::getWeight(ui node, ui node_two) {
 double weight;
	double a = (arr_nodes[node][1] - arr_nodes[node_two][1]) * (arr_nodes[node][1] - arr_nodes[node_two][1]);
	double b = (arr_nodes[node][2] - arr_nodes[node_two][2]) * (arr_nodes[node][2] - arr_nodes[node_two][2]);
	weight = sqrtl(a + b);
	return weight;
}

double Graph::getSolutionWeight() {
	return solution_wei;
}

//void Graph::addLength(double length) {
//	solution_wei += length;
//}

void Graph::routeLength() {
	solution_wei = 0;
	for (ui i = 0; i < solution.size() - 2; i++)
		solution_wei += getWeight(solution[i], solution[i + 1]);
	solution_wei += getWeight(solution[solution.size() - 2], solution[0]);
	exchange(getNode(0), getNodes());
}

ui Graph::getNodes() {
	return nodes;
}

ui Graph::getNode(ui index) {
	return solution[index];
}

void Graph::push(ui node) {
	solution.insert(solution.end(), node);
}

void Graph::exchange(ui node, ui index) {
	solution[index] = node;
}

//void Graph::deleteOneWeight(ui index) {
//	solution_wei -= getWeight(solution[index], solution[index + 1]);
//}

void Graph::print() {
	for (auto i = solution.begin(); i != solution.end(); ++i)
    std::cout << *i + 1 << ' ';
}