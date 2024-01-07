#pragma once

#include "allocator.h"

namespace Core::Allocator {
    /**
     * Linear allocation.
     * Allocate memory one after the other. It's not possible to deallocate
     */
    class LinearAllocator: public Allocator {

    public:
        LinearAllocator(size_t size, void* start);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;
        void* getCurrentFree();
    private:
        void* _current_free;
    };
}
