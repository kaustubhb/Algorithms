/*
 * Prims.cpp
 *
 *  Created on: 17-Dec-2014
 *      Author: kaustubh
 */
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

struct EdgeNode {
	int from;	// not really necessary
	int to;
	int weight;
};

class PrimsGraph {
public:

	PrimsGraph(int nv, int ne, istream &is = std::cin) {
		nvertices = nv;
		nedges = ne;
		readGraph(is);
	}

	vector<vector<EdgeNode> > adjList;
	//vector<int> vertices;
	int nvertices;
	int nedges;

private:
	void readGraph(istream &is);
	vector<int> distances;
};

void PrimsGraph::readGraph(istream &is) {
	for(int i=0;i<nvertices;++i) {
		adjList.push_back(vector<EdgeNode>());
		distances.push_back(-1);
	}

	for(int i=0;i<nedges;++i) {
		EdgeNode ed;
		int x,y, weight;
		is >> x >> y >> weight;
		ed.from = x;
		ed.to = y;
		ed.weight = weight;

		adjList[x].push_back(ed);
	}
}


int main() {


	return 0;
}



