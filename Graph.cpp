#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
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

	void read_graph(graph *g, bool directed, istream& is) {
		initialize_graph(g, directed);

		int m;		// no of edges
		is >> g->nvertices >> m;

		for (int i = 1; i <= m; ++i) {
			int x, y;	// edge from vertex x to y
			is >> x >> y;
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
		for (int i = 1; i <= g->nvertices; ++i) {
			edgenode *node = g->edges[i];
			while(node != NULL) {
				cout << "(" << i << ", " << node->y << ")  ";
				node = node->next;
			}
			cout << endl;
		}
	}


	void bfs_traversal(graph *g, int start) {
		// initialize visited array
		bool visited[MAXV+1];
		bool processed[MAXV+1];
		for(int i=0;i<=MAXV;++i)
			visited[i] = false;
		for(int i=0;i<=MAXV;++i)
			processed[i] = false;

		std::deque<int> queue;
		queue.push_back(start);
		visited[start] = true;
		while(!queue.empty()) {

			int front = queue[0];
			queue.pop_front();

			cout << "At vertex " << front << endl;

			// for all outgoing edges from front
			edgenode *edge = g->edges[front];
			while(edge != NULL) {
				if(!visited[edge->y]) {
					queue.push_back(edge->y);
					visited[edge->y] = true;
				}
				if(g->directed || !processed[edge->y])
					cout << "(" << front << ", " << edge->y << ")  " << endl;
				edge = edge->next;
			}
			processed[front] = true;
		}
	}

	// tests
	void testGraphCreation() {

		// Directed Graph
		graph g;
		cout << "Creating directed graph" << endl;
		initialize_graph(&g, false);
		ifstream ifs("graph1.txt");
		read_graph(&g, false, ifs);
		print_graph(&g);

		// Undirected graph
		graph g2;
		cout << "Now creating an undirected graph" << endl;
		initialize_graph(&g2, false);
		ifstream ifs2("graph2.txt");
		read_graph(&g2, false, ifs2);
		print_graph(&g2);
	}

	void test_bfs_traversal() {
		graph g;
		cout << "Creating undirected graph" << endl;
		initialize_graph(&g, false);
		ifstream ifs("resources/graph_bfs.txt");
		read_graph(&g, false, ifs);
		bfs_traversal(&g, 1);
	}
}
