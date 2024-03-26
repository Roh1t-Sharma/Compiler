#include <iostream>
#include <vector>
#include <algorithm>
#include "include/Heap.h"
//#include "src/Heap.cpp"
#include "include/HashTable.h"

int main() {

    HashTable dictionary;
    dictionary.insert("Apple","32");
    dictionary.insert("Apricot","20");
    dictionary.insert("Banana", "49");
    dictionary.insert("Mango","45");
    dictionary.insert("Mango");
    dictionary.insert("Pineapple", "22");
    dictionary.insert("Peach", "66");

    dictionary.displayTable();
    dictionary.logMemoryUsage();
    std::cout << dictionary.get("Mango") << std::endl;


    return 0;
}
////uncomment for task1
//
//int main() {
//    Heap heap;
//
//    // Demo: Request five memory blocks of different sizes
//    heap.allocate(100);
//    heap.allocate(200);
//    heap.allocate(300);
//    heap.allocate(400);
//    heap.allocate(500);
//    heap.logMemoryUsage();
//
//    // Free up memory for blocks 2 and 4
//    heap.free(heap.blocks[1].segmentAddress); // Simulating the address
//    heap.free(heap.blocks[3].segmentAddress);
//
//    // Free up memory for block 3
//    heap.free(heap.blocks[2].segmentAddress);
//
//    // Request slightly larger memory than can be allocated for one segment
//    heap.allocate(heap.MAX_HEAP_SIZE); // This will fail the allocation
//
//    // Request memory half the size from the previous point three times
//    size_t requestSize = heap.MAX_HEAP_SIZE / 2 / 3;
//    heap.allocate(requestSize);
//    heap.allocate(requestSize);
//    heap.allocate(requestSize);
//
//    // Log memory usage
//    heap.logMemoryUsage();
//    return 0;
//}