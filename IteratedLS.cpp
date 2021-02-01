#include "Graph.h"
#include <ctime>

void Greedy(Graph& graph) {
	std::vector <bool> arr(graph.getNodes(), false);
	srand(time(0));
	ui first = rand() % graph.getNodes();
	ui node = first;
	arr[node] = true;
	ui number = 1;
	ui new_node = 0;
	graph.push(node);
	while (number < graph.getNodes()) {
		double min = 10000000000000;
		for (ui i = 0; i < graph.getNodes(); i++) {
			if (i != node && !arr[i] && min > graph.getWeight(node, i)) {
				min = graph.getWeight(node, i);
				new_node = i;
			}
		}
		//graph.addLength(min);
		node = new_node;
	 graph.push(node);
		number++;
		arr[node] = true;
	}
	graph.push(first);
	//graph.addLength(graph.getWeight(node, first));
	graph.routeLength();
}

////пусть первый и второй - это индексы вершин, порядок которых изменяем
//Graph swap(Graph graph, ui first, ui second) {
//	Graph new_route(graph);
//	int f = first;
//	int s = second;
//	while ((f != s) && ((s - f) > 0)) {
//		//меняем местами два элемента
//		new_route.change(f, s);
//		f++;
//		s--;
//	}
//	//удаляем вес, который получен связями с first и second элементами, потому что теперь first - 1 связан с second, а first - c second + 1
//	if (first > 0) {
//		new_route.deleteOneWeight(first - 1);
//		new_route.addLength(new_route.getWeight(first - 1, second));
//	}
//	if (second < graph.getNodes() - 1) {
//		new_route.deleteOneWeight(second);
//	 new_route.addLength(new_route.getWeight(second + 1, first));
//	}
//	/*if (first == 0) {
//		new_route.deleteOneWeight(graph.getNodes() - 2);
//		new_route.addLength(new_route.getWeight(graph.getNodes() - 1, second));
//		new_route.change(graph.getNodes(), first);
//	}*/
//	return new_route;
//}
//
//void LocalSearch(Graph& graph) {
//	double min = graph.getSolutionWeight();
//	for (int i = 0; i < graph.getNodes() - 1; i++) {
//		for (int j = i + 1; j < graph.getNodes(); j++) {
//			Graph tmp = swap(graph, i, j);
//			if (tmp.getSolutionWeight() < min) {
//				min = tmp.getSolutionWeight();
//				graph = tmp;
//			}
//		}
//	}
//}

Graph two_opt_swap(Graph graph, int first, int second) {
	Graph new_graph(graph);
	ui f = first;
	for (int i = second; i >= first; i--)
		new_graph.exchange(graph.getNode(i), f++);
	return new_graph;
}

void LocalSearch(Graph& graph) {
	double min = graph.getSolutionWeight();
  for (ui i = 0; i < graph.getNodes() - 1; i++) {
		for (ui j = i + 1; j < graph.getNodes(); j++) {
			Graph tmp = two_opt_swap(graph, i, j);
   tmp.routeLength();
			if (tmp.getSolutionWeight() < min) {
				min = tmp.getSolutionWeight();
				graph = tmp;
			}
		}
	}
}

Graph double_bridge(Graph graph) {
	Graph new_graph(graph);
	ui first = rand() % graph.getNodes() / 4;
	ui second = first + rand() % graph.getNodes() / 4;
	ui third = second + rand() % graph.getNodes() / 4;
	ui f = first;
	for (ui i = second; i < third; i++)
		new_graph.exchange(graph.getNode(i), f++);
	for (ui i = first ; i < second; i++)
		new_graph.exchange(graph.getNode(i), f++);
	return new_graph;
}

void IteratedLocalSearch(Graph& graph) {
	Greedy(graph);
	std::cout << std::setprecision(15) << graph.getSolutionWeight() << std::endl;
	graph.print();
	std::cout << std::endl;

	LocalSearch(graph);
	std::cout << std::setprecision(15) << graph.getSolutionWeight() << std::endl;
	graph.print();
	std::cout << std::endl;

	double min = graph.getSolutionWeight();

	for (ui i = 0; i < 7; i++) {
		Graph new_graph(graph);
		new_graph = double_bridge(new_graph);
		new_graph.routeLength();
		LocalSearch(new_graph);
		if (min > new_graph.getSolutionWeight()) {
			min = new_graph.getSolutionWeight();
			graph = new_graph;
		}
	}
}