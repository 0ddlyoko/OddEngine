#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Core::Allocator {
    /**
     * Fast memory allocation with memory leak detection.
     * "Allocator" is an abstract class that will be implemented by custom allocator type, as LinearAllocator, StackAllocator, ...
     */
    class Allocator {

    public:
        Allocator(size_t size, void* start);
        ~Allocator();

        [[nodiscard]] virtual void* allocate(size_t size, uint8_t alignment) = 0;
        virtual void deallocate(void* p) = 0;
        virtual void clear() = 0;
        [[nodiscard]] void* getStart() const;
        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] size_t getUsedMemory() const;
        [[nodiscard]] size_t getNumAllocations() const;

    protected:
        void* _start;
        size_t _size;
        size_t _used_memory;
        size_t _num_allocations;
    };

    template <class T, class... Args>
    T* allocate(Allocator& allocator, Args&&... args);

    template <class T>
    void deallocate(Allocator& allocator, T* object);

    template <class T>
    T* allocateArray(Allocator& allocator, size_t length);

    template <class T>
    T* allocateArrayNoConstruct(Allocator& allocator, size_t length);

    template <class T>
    void deallocateArray(Allocator& allocator, T* array);

    template <class T>
    void deallocateArrayNoDestruct(Allocator& allocator, T* array);
}
