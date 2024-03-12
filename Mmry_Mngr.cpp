#include <iostream>
#include <vector>
#include <algorithm>

// Defines a structure for each memory block
struct MemoryBlock {
    size_t size; // Size of the block
    bool inUse; // Whether the block is in use or not
    void* segmentAddress; // Address of the block in the heap

    MemoryBlock(size_t sz, void* addr) : size(sz), inUse(true), segmentAddress(addr) {}
};

class Heap {
private:
    // Stores information about all memory blocks
    // Maximum heap size for demo purposes
    size_t usedMemory = 0; // Tracks the amount of used memory

public:
    void* allocate(size_t size) {
        if (usedMemory + size > MAX_HEAP_SIZE) {
            std::cout << "Allocation failed: Not enough memory.\n";
            return nullptr; // Allocation failure code
        }

        // Simulate memory allocation (for demo purposes, we don't use real memory allocation)
        void* segmentAddress = reinterpret_cast<void*>(usedMemory);
        blocks.emplace_back(size, segmentAddress);
        usedMemory += size;

        std::cout << "Allocated " << size << " bytes. Total used memory: " << usedMemory << " bytes.\n";
        return segmentAddress;
    }

    void free(void* segmentAddress) {
        auto it = std::find_if(blocks.begin(), blocks.end(), [segmentAddress](const MemoryBlock& block) {
            return block.segmentAddress == segmentAddress;
        });

        if (it != blocks.end()) {
            it->inUse = false;
            std::cout << "Freed memory block at " << it->segmentAddress << ". Size: " << it->size << " bytes.\n";
        } else {
            std::cout << "Free failed: No matching memory block found.\n";
        }
    }

    void logMemoryUsage() {
        std::cout << "\nMemory Usage Report:\n";
        std::cout << "Total memory reserved: " << MAX_HEAP_SIZE << " bytes\n";
        std::cout << "Total memory used: " << usedMemory << " bytes\n";
        for (const auto& block : blocks) {
            std::cout << "Block at " << block.segmentAddress << " - Size: " << block.size << " bytes, Status: " << (block.inUse ? "In Use" : "Not In Use") << "\n";
        }
    }

    const size_t MAX_HEAP_SIZE = 1024 * 1024;
    std::vector<MemoryBlock> blocks;
};

int main() {
    Heap heap;

    // Demo: Request five memory blocks of different sizes
    heap.allocate(100);
    heap.allocate(200);
    heap.allocate(300);
    heap.allocate(400);
    heap.allocate(500);

    // Free up memory for blocks 2 and 4
    heap.free(heap.blocks[1].segmentAddress); // Simulating the address
    heap.free(heap.blocks[3].segmentAddress);

    // Free up memory for block 3
    heap.free(heap.blocks[2].segmentAddress);

    // Request slightly larger memory than can be allocated for one segment
    heap.allocate(heap.MAX_HEAP_SIZE); // This should fail

    // Request memory half the size from the previous point three times
    size_t requestSize = heap.MAX_HEAP_SIZE / 2 / 3;
    heap.allocate(requestSize);
    heap.allocate(requestSize);
    heap.allocate(requestSize);

    // Log memory usage
    heap.logMemoryUsage();

    return 0;
}