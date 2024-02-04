
#include <utility>
#include "allocator.h"

namespace core::allocator {

    Allocator::Allocator(size_t size, void *start): _size(size), _start(start), _used_memory(0), _num_allocations(0) {}
    Allocator::~Allocator() {
//        assert(_used_memory == 0 && _num_allocations == 0);
        _start = nullptr;
        _size = 0;
    }

    void* Allocator::getStart() const { return _start; }
    size_t Allocator::getSize() const { return _size; }
    size_t Allocator::getUsedMemory() const { return _used_memory; }
    size_t Allocator::getNumAllocations() const { return _num_allocations; }

    template <class T, class... Args>
    T* allocate(Allocator& allocator, Args&&... args) {
        return new (allocator.allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
    }

    template <class T>
    void deallocate(Allocator& allocator, T* object) {
        object->~T();
        allocator.deallocate(object);
    }

    template <class T>
    T* allocateArray(Allocator& allocator, size_t length) {
        T* list = allocateArrayNoConstruct<T>(allocator, length);
        // Instantiate T
        for (size_t i = 0; i < length; i++)
            new (list + i) T();
        return list;
    }

    template <class T>
    T* allocateArrayNoConstruct(Allocator& allocator, size_t length) {
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
    void deallocateArray(Allocator& allocator, T* array) {
        size_t length = *(((size_t *) array) - 1);

        // Destruct elements
        for (size_t i = length - 1; i > 0; i--)
            array[i].~T();

        deallocateArrayNoDestruct(allocator, array);
    }

    template <class T>
    void deallocateArrayNoDestruct(Allocator& allocator, T* array) {
        uint8_t header_size = sizeof(size_t) / sizeof(T);
        if (sizeof(size_t) % sizeof(T) > 0)
            header_size++;

        allocator.deallocate(array - header_size);
    }
}
