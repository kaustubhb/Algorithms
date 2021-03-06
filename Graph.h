#ifndef __GRAPH__
#define __GRAPH__

#define MAXV 1000	// Maximum number of vertices
#include <istream>
#include <iostream>
#include <vector>

struct edgenode {
	int y;		// adjacency info ?
	int weight;		// edge weight, if any
	struct edgenode *next;
};

class graph {
public:

	enum COLOR {
		UNCOLORED,
		BLACK,
		WHITE
	};

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
	bool isTwoColorGraph();
	void dfs_traversal(int start=1);
	int getParent(int i) {return parent[i];};
	void topologicalSort();

private:
	void read_graph(bool directed, std::istream &is = std::cin);
	bool visited[MAXV+1], processed[MAXV+1];
	int parent[MAXV+1];
	int entryTime[MAXV+1], exitTime[MAXV+1];
	bool bfsTwoColor(std::vector<COLOR> colors, int start=1);
	void colorMe(std::vector<COLOR> colors, int i, COLOR parentColor);
	void dfs_travel_internal(int start);
	void dfs_topological(int x);
	int time;
};

class test_graphs {
public:
	static void graphCreation();
	static void bfs_traversal();
	static void connected_componenets();
	static void twoColor();
	static void dfs_traversal();
	static void testTopological();
};

#endif
