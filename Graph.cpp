#include "Graph.h"
#include <cstdlib>
#include <iostream>
using namespace std;

namespace Graphs {
	void initialize_graph(graph* g, bool directed) {
		g->nvertices = 0;
		g->nedges = 0;
		g->directed = directed;

		for (int i = 1; i <= MAXV; ++i)		// starts with 1. I guess 0 is just ignored?
			g->degree[i] = 0;
		for (int i = 1; i <= MAXV; ++i)
			g->edges[i] = NULL;

	}

	void read_graph(graph *g, bool directed) {
		initialize_graph(g, directed);

		int m;		// no of edges
		cin >> g->nvertices >> m;

		for (int i = 1; i <= m; ++i) {
			int x, y;	// edge from vertex x to y
			cin >> x >> y;
			insert_edge(g, x, y, directed);
		}
	}

	void insert_edge(graph *g, int x, int y, bool directed) {
		edgenode *p;	
		p = new edgenode;
		p->weight = 0;
		p->y = y;

		//insert p at the head of linked list for vertex x's edges
		p->next = g->edges[x];
		g->edges[x] = p;
		g->degree[x]++;

		if (!directed)
			insert_edge(g, y, x, true);
		else
			++(g->nedges);
	}

	void print_graph(graph *g) {
		for (int i = 0; i < g->nvertices; ++i) {
			cout << 
		}
	}
}