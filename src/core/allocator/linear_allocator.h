#pragma once

#include "allocator.h"

namespace core::allocator {
    /**
     * Linear allocation.
     * Allocate memory one after the other. It's not possible to deallocate
     */
    class LinearAllocator: public Allocator {

    public:
        LinearAllocator(size_t size, void* start);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;
        [[nodiscard]] void* getCurrentFree() const;
    private:
        void* _current_free;
    };
}
