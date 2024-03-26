//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <utility>
//
//struct MemoryBlock {
//   size_t size; // Size of the block
//   bool inUse; // Whether the block is in use or not
//   void* segmentAddress; // Address of the block in the heap
//
//   MemoryBlock(size_t sz, void* addr) : size(sz), inUse(true), segmentAddress(addr) {}
//};
//
//class Heap {
//private:
//   std::vector<MemoryBlock> blocks;
//   const size_t MAX_HEAP_SIZE = 1024 * 1024; // Maximum heap size for demo purposes
//   size_t usedMemory = 0; // Tracks the amount of used memory
//
//public:
//   void* allocate(size_t size) {
//       if (usedMemory + size > MAX_HEAP_SIZE) {
//           std::cout << "Allocation failed: Not enough memory.\n";
//           return nullptr; // Allocation failure
//       }
//
//       // Simulate memory allocation
//       void* segmentAddress = reinterpret_cast<void*>(usedMemory);
//       blocks.emplace_back(size, segmentAddress);
//       usedMemory += size;
//
//       std::cout << "Allocated " << size << " bytes. Total used memory: " << usedMemory << " bytes.\n";
//       return segmentAddress;
//   }
//
//   void free(void* segmentAddress) {
//       auto it = std::find_if(blocks.begin(), blocks.end(), [segmentAddress](const MemoryBlock& block) {
//           return block.segmentAddress == segmentAddress && block.inUse;
//           });
//
//       if (it != blocks.end()) {
//           it->inUse = false;
//           usedMemory -= it->size; // Assuming we can reduce used memory when block is freed
//           std::cout << "\nFreed memory block at " << it->segmentAddress << ". Size: " << it->size << " bytes.\n";
//       }
//       else {
//           std::cout << "Free failed: No matching memory block found.\n";
//       }
//   }
//
//   void logMemoryUsage() const {
//       std::cout << "\nMemory Usage Report:\n";
//       std::cout << "Total memory reserved: " << MAX_HEAP_SIZE << " bytes\n";
//       std::cout << "Total memory used: " << usedMemory << " bytes\n";
//       for (const auto& block : blocks) {
//           std::cout << "Block at " << block.segmentAddress << " - Size: " << block.size << " bytes. Status: " << (block.inUse ? "Used" : "Free") << "\n";
//       }
//   }
//};
//
//class List {
//public:
//   virtual void push(int value) = 0;
//   virtual int pop() = 0;
//   virtual void print() const = 0;
//   virtual void logMemoryUsage() const {
//       heap.logMemoryUsage();
//   }
//   virtual ~List() {}
//
//protected:
//   Heap heap; // Use the provided Heap for memory management
//   std::vector<std::pair<int, void*>> data; // Store value and pointer to its memory block
//
//   void log(const std::string& action) {
//       std::cout << action << ": ";
//       print();
//   }
//};
//
//class Stack : public List {
//public:
//   void push(int value) override {
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.push_back({ value, addr });
//           log("Push to Stack");
//       }
//   }
//
//   int pop() override {
//       if (data.empty()) {
//           std::cerr << "Stack is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.back();
//       int value = valPtr.first;
//       data.pop_back();
//       heap.free(valPtr.second);
//       log("Pop from Stack");
//       return value;
//   }
//
//   void print() const override {
//       for (const auto& valPtr : data) std::cout << valPtr.first << " ";
//       std::cout << std::endl;
//   }
//};
//
//class Queue : public List {
//public:
//   void push(int value) override {
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.push_back({ value, addr });
//           log("Enqueue to Queue");
//       }
//   }
//   void push_front(int value) {
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.insert(data.begin(), { value, addr });
//           log("Push Front to Dequeue");
//       }
//   }
//
//   void push_back(int value) { // Removed the 'override' specifier
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.push_back({ value, addr });
//           log("Push Back to Dequeue");
//       }
//   }
//   int pop() override {
//       if (data.empty()) {
//           std::cerr << "Queue is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.front();
//       int value = valPtr.first;
//       data.erase(data.begin());
//       heap.free(valPtr.second);
//       log("Dequeue from Queue");
//       return value;
//   }
//   int pop_front() {
//       if (data.empty()) {
//           std::cerr << "Dequeue is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.front();
//       int value = valPtr.first;
//       data.erase(data.begin());
//       heap.free(valPtr.second);
//       log("Pop Front from Dequeue");
//       return value;
//   }
//
//   int pop_back() { // Removed the 'override' specifier
//       if (data.empty()) {
//           std::cerr << "Dequeue is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.back();
//       int value = valPtr.first;
//       data.pop_back();
//       heap.free(valPtr.second);
//       log("Pop Back from Dequeue");
//       return value;
//   }
//
//   void print() const override {
//       for (const auto& valPtr : data) std::cout << valPtr.first << " ";
//       std::cout << std::endl;
//   }
//};
//
//class Dequeue : public List {
//public:
//   void push_front(int value) {
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.insert(data.begin(), { value, addr });
//           log("Push Front to Dequeue");
//       }
//   }
//
//   void push_back(int value) { // Removed the 'override' specifier
//       void* addr = heap.allocate(sizeof(int));
//       if (addr) {
//           data.push_back({ value, addr });
//           log("Push Back to Dequeue");
//       }
//   }
//
//   int pop_front() {
//       if (data.empty()) {
//           std::cerr << "Dequeue is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.front();
//       int value = valPtr.first;
//       data.erase(data.begin());
//       heap.free(valPtr.second);
//       log("Pop Front from Dequeue");
//       return value;
//   }
//
//   int pop_back() { // Removed the 'override' specifier
//       if (data.empty()) {
//           std::cerr << "Dequeue is empty!" << std::endl;
//           return -1; // Error code
//       }
//       auto valPtr = data.back();
//       int value = valPtr.first;
//       data.pop_back();
//       heap.free(valPtr.second);
//       log("Pop Back from Dequeue");
//       return value;
//   }
//
//   // The push and pop functions should override the List base class functions
//   void push(int value) override {
//       push_back(value);
//   }
//
//   int pop() override {
//       return pop_front();
//   }
//
//   void print() const override {
//       for (const auto& valPtr : data) std::cout << valPtr.first << " ";
//       std::cout << std::endl;
//   }
//};
//
//int main() {
//
//   Stack s;
//   s.push(2);
//   s.push(3);
//   s.push(1);
//   s.pop(); // Should pop 3, showing memory deallocation
//
//   Queue q;
//   q.push(2);
//   q.push(1);
//   q.push(3);
//
//   Dequeue d;
//   d.push_front(1);
//   d.push_front(2); // Now 2 is at the beginning
//   d.push_back(3);
//   d.pop_front(); // Should pop 2, showing memory deallocation
//   d.pop_back(); // Should pop 3, showing memory deallocation
//   d.pop(); // Should pop 1, now Dequeue is empty and showing deallocation
//
//   s.logMemoryUsage();
//   q.logMemoryUsage();
//   d.logMemoryUsage();
//
//   return 0;
//}
