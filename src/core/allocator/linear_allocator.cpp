
#include "linear_allocator.h"
#include "../util/pointer_math.h"

namespace Core::Allocator {
    LinearAllocator::LinearAllocator(size_t size, void *start) : Allocator(size, start), _current_free(start) {}

    void *LinearAllocator::allocate(size_t size, uint8_t alignment) {
        size_t adjustment = Core::Util::PointerMath::getAlignment(_current_free, alignment);

        if (_used_memory + adjustment + size > _size) return nullptr;

        uintptr_t current_free = (uintptr_t) _current_free + adjustment;

        _current_free = (void *) (current_free + size);
        _used_memory += adjustment + size;
        _num_allocations++;

        return (void *) current_free;
    }

    void LinearAllocator::deallocate(void *p) {
        // Cannot deallocate in a linear allocator
    }

    void *LinearAllocator::getCurrentFree() const {
        return _current_free;
    }
}
