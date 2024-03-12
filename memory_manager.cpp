//#include <iostream>
//#include <vector>
//#include <optional>
//
//struct MemoryBlock {
//    size_t size;
//    bool inUse;
//    size_t startAddress;
//
//    MemoryBlock(size_t sz, size_t startAddr) : size(sz), inUse(false), startAddress(startAddr) {}
//};
//
//class MemoryManager {
//private:
//    std::vector<MemoryBlock> blocks;
//    size_t totalMemory;
//    size_t usedMemory = 0;
//
//public:
//    explicit MemoryManager(size_t totalMem) : totalMemory(totalMem) {}
//
//    std::optional<size_t> allocate(size_t size) {
//        if (usedMemory + size > totalMemory) {
//            std::cout << "Allocation failed: Not enough memory." << std::endl;
//            return std::nullopt; // C++17 way to indicate failure
//        }
//        size_t startAddress = usedMemory;
//        blocks.emplace_back(size, startAddress);
//        blocks.back().inUse = true;
//        usedMemory += size;
//        return startAddress;
//    }
//
//    bool release(size_t startAddress) {
//        for (auto& block : blocks) {
//            if (block.startAddress == startAddress && block.inUse) {
//                block.inUse = false;
//                usedMemory -= block.size;
//                std::cout << "Memory block starting at " << startAddress << " released." << std::endl;
//                return true;
//            }
//        }
//        std::cout << "Release failed: Block not found or already released." << std::endl;
//        return false;
//    }
//
//    void logMemoryUsage() const {
//        std::cout << "Total Memory: " << totalMemory << std::endl;
//        std::cout << "Used Memory: " << usedMemory << std::endl;
//        for (const auto& block : blocks) {
//            std::cout << "Block Start Address: " << block.startAddress
//                      << ", Size: " << block.size
//                      << ", Status: " << (block.inUse ? "In Use" : "Not Used") << std::endl;
//        }
//    }
//};
//
//int main() {
//    MemoryManager mm(1000); // Initialize with 1000 units of memory
//
//    auto addr1 = mm.allocate(100);
//    if (addr1) { std::cout << "Allocated 100 units at address " << addr1.value() << std::endl; }
//
//    auto addr2 = mm.allocate(200);
//    if (addr2) { std::cout << "Allocated 200 units at address " << addr2.value() << std::endl; }
//    mm.logMemoryUsage();
//
//    if (addr1) {
//        mm.release(addr1.value());
//    }
//    mm.logMemoryUsage();
//
//    return 0;
//}