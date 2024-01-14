

add_library(core
        allocator/allocator.cpp
        util/pointer_math.inl
        util/pointer_math.cpp
        allocator/block_allocation.cpp
        allocator/freelist_allocator.cpp
        allocator/linear_allocator.cpp
        allocator/stack_allocator.cpp
)
