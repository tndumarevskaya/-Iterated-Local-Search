#ifndef INCLUDE_GRAPH_H_
#define INCLUDE_GRAPH_H_

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>

typedef unsigned int ui;

class Graph {
private:
	ui nodes;
	std::vector <std::vector <ui>> arr_nodes;
	std::vector <ui> solution;
	double solution_wei;
public:
	explicit Graph() {
		nodes = 0;
		solution_wei = 0;
	}
	explicit Graph(ui n) : nodes{ n } {
		solution_wei = 0;
		arr_nodes.resize(nodes);
		for (ui i = 0; i < nodes; i++)
			arr_nodes[i].resize(3);
	}
	explicit Graph(ui n, std::ifstream file) : nodes{ n } {
		solution_wei = 0;
		arr_nodes.resize(nodes);
		for (ui i = 0; i < nodes; i++) {
			arr_nodes[i].resize(3);
			for (int j = 0; j < 3; j++)
				file >> arr_nodes[i][j];
		}
	}
	Graph(const Graph& graph) {
	 nodes = graph.nodes;
	 arr_nodes = graph.arr_nodes;
	 solution = graph.solution;
	 solution_wei = graph.solution_wei;
	}
	double getWeight(ui, ui);
	double getSolutionWeight();
	ui getNodes();
	ui getNode(ui index);
	void addLength(double length);
	void routeLength();
	void push(ui);
	void exchange(ui first_index, ui second_index);
	void deleteOneWeight(ui index);
	void print();
};

void Greedy(Graph& graph);
void LocalSearch(Graph& graph);
void IteratedLocalSearch(Graph& graph);

#endif