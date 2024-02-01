#include <iostream>
#include "core/util/pointer_math.h"

typedef short my_size;

int main() {
//    std::cout << "Hello, World!" << std::endl;
    int a[4] = {1, 42, 4, 8};

//    uint8_t b = sizeof(size_t) / 16;
//    uint8_t c = sizeof(size_t) % 16;
//    std::cout << "sizeof(size_t): " << sizeof(size_t) << std::endl;
//    std::cout << "sizeof(my_size): " << 16 << std::endl;
//    std::cout << unsigned(b) << std::endl;
//    std::cout << unsigned(c) << std::endl;

    int* b = a;

//    std::cout << a << std::endl;
//    std::cout << b << std::endl;
//    std::cout << (b + 1) << std::endl;

    std::cout << b << std::endl;
    void* c = Core::Util::PointerMath::add(b, 4);
    std::cout << c << std::endl;

    std::cout << unsigned(Core::Util::PointerMath::getAlignment(reinterpret_cast<const void *>(47), 8)) << std::endl;



    size_t block_size = 9;
    uint8_t alignment = 4;
    size_t real_block_size = (size_t) Core::Util::PointerMath::align((void*) block_size, alignment);
    std::cout << real_block_size << std::endl;



    return 0;
}
