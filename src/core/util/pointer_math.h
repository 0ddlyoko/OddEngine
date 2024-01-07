#pragma once

#include <cstddef>
#include <cstdint>

/**
 * Pointer related math operation.
 * Inspired by https://github.com/tiagovcosta/aquaengine/blob/aea6de9f47ba0243b90c144dee4422efb2389cc7/AquaEngine/Utilities/PointerMath.h#L73
 */
namespace Core::Util::PointerMath {

    /**
     * Check if given pointer is aligned with given alignment.
     * A pointer is aligned with a given alignment if the modulo between the pointer and the alignment is
     * equals to 0
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    bool isAligned(const void* p, uint8_t alignment);

    /**
     * Check if given pointer is aligned with given alignment.
     * A pointer is aligned with a given alignment if the modulo between the pointer and the alignment is
     * equals to 0
     *
     * @tparam T The template
     * @param p  The pointer
     * @return
     */
    template <class T>
    bool isAligned(const T* p);

    /**
     * Retrieves the alignment of given pointer with given alignment.
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    uint8_t getAlignment(const void* p, uint8_t alignment);

    /**
     * Retrieves the alignment of given pointer with given alignment.
     *
     * @tparam T        The template
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    template <class T>
    uint8_t getAlignWithHeader(const void* p, uint8_t alignment);

    /**
     * Retrieves the alignment of given pointer with given alignment.
     *
     * @param p         The pointer
     * @param size      The size of the template
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    uint8_t getAlignWithHeader(const void* p, size_t size, uint8_t alignment);

    /**
     * Retrieves the alignment of given pointer with given alignment, but backward (to the left).
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    uint8_t getBackwardAlignment(const void* p, uint8_t alignment);

    /**
     * Align given pointer with given alignment
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    void* align(void* p, uint8_t alignment);

    /**
     * Align given pointer with given alignment
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    const void* align(const void* p, uint8_t alignment);

    /**
     * Align given pointer with given alignment, but backward (to the left).
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    void* alignBackward(void* p, uint8_t alignment);

    /**
     * Align given pointer with given alignment, but backward (to the left).
     *
     * @param p         The pointer
     * @param alignment The alignment. Must be a power of 2
     * @return
     */
    const void* alignBackward(const void* p, uint8_t alignment);

    /**
     * Add a given amount of size to the pointer.
     * In fact, we only move the pointer by x bytes to the right
     *
     * @param p The pointer
     * @param x The amount to increment
     * @return A new pointer pointing to the original pointer + the given amount
     */
    inline void* add(void* p, size_t x);

    /**
     * Add a given amount of size to the pointer.
     * In fact, we only move the pointer by x bytes to the right
     *
     * @param p The pointer
     * @param x The amount to increment
     * @return A new pointer pointing to the original pointer + the given amount
     */
    inline const void* add(const void* p, size_t x);

    /**
     * Remove a given amount of size from the pointer.
     * In fact, we only move the pointer by x bytes to the left
     *
     * @param p The pointer
     * @param x The amount to decrement
     * @return A new pointer pointing to the original pointer - the given amount
     */
    inline void* remove(void* p, size_t x);

    /**
     * Remove a given amount of size from the pointer.
     * In fact, we only move the pointer by x bytes to the left
     *
     * @param p The pointer
     * @param x The amount to decrement
     * @return A new pointer pointing to the original pointer - the given amount
     */
    inline const void* remove(const void* p, size_t x);
}

#include "pointer_math.inl"
