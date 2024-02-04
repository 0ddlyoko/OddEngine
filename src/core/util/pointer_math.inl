#pragma once

namespace core::util::pointer_math {
    template <class T>
    bool isAligned(const T* p) {
        return isAligned(p, alignof(T));
    }

    template <class T>
    uint8_t getAlignWithHeader(const void* p, uint8_t alignment) {
        if (alignof(T) > alignment)
            alignment = alignof(T);

        return sizeof(T) + getAlignment(add(p, sizeof(T)), alignment);
    }

    inline void* add(void* p, size_t x) {
        return (void*) (reinterpret_cast<uintptr_t>(p) + x);
    }

    inline const void* add(const void* p, size_t x) {
        return (const void*) (reinterpret_cast<uintptr_t>(p) + x);
    }

    inline void* remove(void* p, size_t x) {
        return (void*) (reinterpret_cast<uintptr_t>(p) - x);
    }

    inline const void* remove(const void* p, size_t x) {
        return (const void*) (reinterpret_cast<uintptr_t>(p) - x);
    }
}
