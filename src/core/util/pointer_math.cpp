#include "pointer_math.h"

namespace Core::Util::PointerMath {
    bool isAligned(const void* p, uint8_t alignment) {
        return getAlignment(p, alignment) == 0;
    }

    template <class T>
    bool isAligned(const T* p) {
        return isAligned(p, alignof(T));
    }

    uint8_t getAlignment(const void* p, uint8_t alignment) {
        uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(p) & static_cast<uint8_t>(alignment - 1));

        if (alignment == adjustment)
            return 0;

        return adjustment;
    }

    template <class T>
    uint8_t getAlignWithHeader(const void* p, uint8_t alignment) {
        if (alignof(T) > alignment)
            alignment = alignof(T);

        return sizeof(T) + getAlignment(add(p, sizeof(T)), alignment);
    }

    uint8_t getBackwardAlignment(const void* p, uint8_t alignment) {
        uint8_t adjustment = reinterpret_cast<uintptr_t>(p) & static_cast<uint8_t>(alignment - 1);

        if (alignment == adjustment)
            return 0;

        return adjustment;
    }

    void* align(void* p, uint8_t alignment) {
        return add(p, getAlignment(p, alignment));
    }

    const void* align(const void* p, uint8_t alignment) {
        return add(p, getAlignment(p, alignment));
    }

    void* alignBackward(void* p, uint8_t alignment) {
        return remove(p, getBackwardAlignment(p, alignment));
    }

    const void* alignBackward(const void* p, uint8_t alignment) {
        return remove(p, getBackwardAlignment(p, alignment));
    }
}
