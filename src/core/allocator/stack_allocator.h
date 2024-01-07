#pragma once

#include "allocator.h"

namespace Core::Allocator {
    /**
     * Stack allocation.
     */
    class StackAllocator: public Allocator {

    public:
        StackAllocator(size_t size, void* start);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;
        void* getCurrentFree();
        void* getLastAllocator();
    private:

        struct AllocationHeader {
            uint8_t adjustment;
            void* previous_address;
        };

        void* _current_free;
        void* _last_allocation;
    };
}
