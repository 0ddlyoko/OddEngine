#pragma once

#include "allocator.h"

namespace Core::Allocator {
    /**
     * Linear allocation.
     * Allocate memory
     */
    class LinearAllocator: public Allocator {

    public:
        LinearAllocator(size_t size, void* start);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;
        void clear() override;
        void* getCurrentFree();
    private:
        void* _current_free;
    };
}
