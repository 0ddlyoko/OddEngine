
#include <utility>
#include "allocator.h"

namespace Core::Allocator {

    allocator::allocator(size_t size, void *start): _size(size), _start(start), _used_memory(0), _num_allocations(0) {}
    allocator::~allocator() {
        assert(_size == 0 && _num_allocations == 0);
        _start = nullptr;
        _size = 0;
    }

    void* allocator::getStart() const { return _start; }
    size_t allocator::getSize() const { return _size; }
    size_t allocator::getUsedMemory() const { return _used_memory; }
    size_t allocator::getNumAllocations() const { return _num_allocations; }

    template <class T, class... Args>
    T* allocate(allocator& allocator, Args&&... args) {
        return new (allocator.allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
    }

    template <class T>
    void deallocate(allocator& allocator, T* object) {
        object->~T();
        allocator.deallocate(object);
    }

    template <class T>
    T* allocateArray(allocator& allocator, size_t length) {
        T* list = allocateArrayNoConstruct<T>(allocator, length);
        // Instantiate T
        for (size_t i = 0; i < length; i++)
            new (list + i) T();
        return list;
    }

    template <class T>
    T* allocateArrayNoConstruct(allocator& allocator, size_t length) {
        assert(length > 0);
        uint8_t header_size = sizeof(size_t) / sizeof(T);
        if (sizeof(size_t) % sizeof(T) > 0)
            header_size++;

        // Allocate extra space for the header (length of the array)
        T* list = ((T*) allocator.allocate(sizeof(T) * (length + header_size), alignof(T))) + header_size;

        // Set length before the list
        *(((size_t *) list) - 1) = length;
        return list;
    }

    template <class T>
    void deallocateArray(allocator& allocator, T* array) {
        size_t length = *(((size_t *) array) - 1);

        // Destruct elements
        for (size_t i = length - 1; i > 0; i--)
            array[i].~T();

        deallocateArrayNoDestruct(allocator, array);
    }

    template <class T>
    void deallocateArrayNoDestruct(allocator& allocator, T* array) {
        uint8_t header_size = sizeof(size_t) / sizeof(T);
        if (sizeof(size_t) % sizeof(T) > 0)
            header_size++;

        allocator.deallocate(array - header_size);
    }
}
