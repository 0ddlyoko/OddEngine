# Allocators

Allocators are used to have a fast memory allocation with memory leak detection.
We can have different kind of allocators.

- [Linear Allocator](#linear-allocator)
- [Stack Allocator](#stack-allocator)
- [FreeList Allocator](#freelist-allocator)
- [Block Allocator](#block-allocator)

## Linear Allocator
A Linear Allocator is the simplest and fastest type of Allocator.
His goal is to allocate memory one after the next.
Total size, used size and number of allocation are stored.

### Allocations
New allocation will simply move the pointer to the first free forward address.

### Deallocations
Individual deallocations are not possible. You can only clear everything.

## Stack Allocator
A Stack Allocator works like a Stack.
You can allocate memory exactly like the Linear Allocator, but deallocations are a bit different.

### Allocations
New allocation will simply move the pointer to the first free forward address.

### Deallocations
Individual deallocatoins are possible, but, as it's a stack, you can only do it in the reverse order.
So, from the end to the start.

## FreeList Allocator
A FreeList Allocator works like the real memory.
You can allocate memory and deallocate it whenever you want.

### Allocations
New Allocation can be made, and will be set to the first best fit, which will cause less fragmentation than first-fit or worst-fit.

### Deallocations
Individual deallocations can be made.

## Block Allocator
A Block Allocator allocates a bunch of fixed size. This results in a fast allocation and deallocation, without needing to align each allocation since all allocations have the same size.
We store internally a linked list of pointers to free blocks.

### Allocations
New Allocation is made quickly, as we have a pointer to the first free block.

### Deallocations
Deallocation is also fast as we only need to set the block as a free block.
