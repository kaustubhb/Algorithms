/* 
 * File:   Heap.h
 * Author: kaustubh
 *
 * Created on 30 November, 2014, 10:28 AM
 */

#ifndef HEAP_H
#define	HEAP_H

#include <vector>

class MaxHeap {
public:
    std::vector<int> heap;
    
    int lchild(int i) { return i*2 + 1; }
    int rchild(int i) { return i*2 + 2; }
    int parent(int i) { return (i-1)/2; }
    
    bool checkMaxHeap(int i);
    void maxHeapify(int i);
    void buildMaxHeap();
    
private:
    int heapSize;
};

namespace Heaps {
    void testBuildMaxHeap();
}


#endif	/* HEAP_H */

