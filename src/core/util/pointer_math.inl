#pragma once

namespace Core::Util::PointerMath {
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
