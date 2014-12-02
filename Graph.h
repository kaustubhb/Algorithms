#ifndef __GRAPH__
#define __GRAPH__

#define MAXV 1000	// Maximum number of vertices
#include <istream>
#include <iostream>

namespace Graphs {

	struct edgenode {
		int y;		// adjacency info ?
		int weight;		// edge weight, if any
		struct edgenode *next;
	};

	struct graph {
		edgenode *edges[MAXV + 1];	// why maxv + 1? No of edges can be much more than no of vertices
		int degree[MAXV + 1];		// store out degree of each vertex
		int nvertices;				// no of vertices in graph
		int nedges;					// no of edges in graph
		bool directed;
	};

	void initialize_graph(graph* g, bool directed);
	void read_graph(graph *g, bool directed, std::istream &is = std::cin);
	void insert_edge(graph *g, int x, int y, bool directed);
	void print_graph(graph *g);
	void bfs_traversal(graph *g, int start);

	// testing functions
	void testGraphCreation();
	void test_bfs_traversal();
}

#endif
