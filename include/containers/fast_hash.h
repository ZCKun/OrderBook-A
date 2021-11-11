//
// Created by x2h1z on 2021/11/8.
//

#ifndef ORDERBOOK_FAST_HASH_H
#define ORDERBOOK_FAST_HASH_H

#include <cinttypes>

class FastHash
{
public :
    FastHash() = default;
    FastHash(const FastHash&) = default;
    FastHash(FastHash&&) noexcept = default;
    ~FastHash() = default;

    FastHash& operator=(const FastHash&) = default;
    FastHash& operator=(FastHash&&) noexcept = default;

    //! 计算 Hash 值
    size_t operator()(uint64_t value) const noexcept;

    static uint64_t Parse(const char str[8]) noexcept;
};

#include "fast_hash.inl"
#endif //ORDERBOOK_FAST_HASH_H
