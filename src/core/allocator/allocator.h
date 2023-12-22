#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace Core::Allocator {
    /**
     * Fast memory allocation with memory leak detection.
     * "Allocator" is an interface that will be implemented by custom allocator type, as LinearAllocator, StackAllocator, ...
     */
    class allocator {

    public:
        allocator(size_t size, void* start);
        ~allocator();

        [[nodiscard]] virtual void* allocate(size_t size, uint8_t alignment) = 0;
        virtual void deallocate(void* p) = 0;
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
    T* allocate(allocator& allocator, Args&&... args);

    template <class T>
    void deallocate(allocator& allocator, T* object);

    template <class T>
    T* allocateArray(allocator& allocator, size_t length);

    template <class T>
    T* allocateArrayNoConstruct(allocator& allocator, size_t length);

    template <class T>
    void deallocateArray(allocator& allocator, T* array);

    template <class T>
    void deallocateArrayNoDestruct(allocator& allocator, T* array);
}
