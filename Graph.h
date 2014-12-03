#ifndef __GRAPH__
#define __GRAPH__

#define MAXV 1000	// Maximum number of vertices
#include <istream>
#include <iostream>

struct edgenode {
	int y;		// adjacency info ?
	int weight;		// edge weight, if any
	struct edgenode *next;
};

class graph {
public:
	edgenode *edges[MAXV + 1];	// why maxv + 1? No of edges can be much more than no of vertices
	int degree[MAXV + 1];		// store out degree of each vertex
	int nvertices;				// no of vertices in graph
	int nedges;					// no of edges in graph
	bool directed;

	graph(bool directed);

	void read_graph(std::istream &is = std::cin);
	void insert_edge(int x, int y, bool directed);
	void print_graph();
	void bfs_traversal(int start);
	void initialize_search();
	int connected_componenets();

private:
	void read_graph(bool directed, std::istream &is = std::cin);
	bool visited[MAXV+1], processed[MAXV+1];
	int parent[MAXV+1];
};

class test_graphs {
public:
	static void graphCreation();
	static void bfs_traversal();
	static void connected_componenets();
};

#endif
