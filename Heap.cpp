#include "Heap.h"
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

void MaxHeap::maxHeapify(int i) {
    if(i >= heapSize)
        return;
    int largestIdx = i;
    if(lchild(i) < heapSize && heap[lchild(i)] > heap[i]) {
        if(rchild(i) < heapSize && heap[rchild(i)] > heap[lchild(i)]) {
            largestIdx = rchild(i);
        }
        else {
            largestIdx = lchild(i);
        }
    }
    else {
        if(rchild(i) < heapSize && heap[rchild(i)] > heap[i]) {
            largestIdx = rchild(i);
        }
    }
    if(largestIdx != i) {
        std::swap(heap[i], heap[largestIdx]);
        maxHeapify(largestIdx);
    }
}

void MaxHeap::buildMaxHeap() {
    heapSize = heap.size(); 
    int startIdx = heapSize/2 -1;
    
    while(startIdx >= 0) {
        maxHeapify(startIdx);
        --startIdx;
    }
}

bool MaxHeap::checkMaxHeap(int i) {
    int left = lchild(i);
    int right = rchild(i);
    
    if(left < heapSize) {
        if(heap[left] > heap[i]) return false;
        if(!checkMaxHeap(left)) return false;
    }
    if(right < heapSize) {
        if(heap[right] > heap[i]) return false;
        if(!checkMaxHeap(right)) return false;
    }
    return true;
}

namespace Heaps {
void testBuildMaxHeap() {
        MaxHeap mh;
        int heapArr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        for(int i=0; i < sizeof(heapArr); ++i) {
            mh.heap.push_back(heapArr[i]);
        }
        
        mh.buildMaxHeap();
        assert(mh.checkMaxHeap(0));
    }

}
