#pragma once
#include <memory>
#include "types.h"

struct Symbol
{
    int id;
    char code[8];
    x2h::type::data::Exchange exchange;

    Symbol() noexcept = default;
    Symbol(int id, const char name[8], const x2h::type::data::Exchange exchange) noexcept;
    Symbol(const Symbol&) noexcept = default;
    Symbol(Symbol&&) noexcept = default;
    ~Symbol() noexcept = default;

    Symbol& operator=(const Symbol&) noexcept = default;
    Symbol& operator=(Symbol&&) noexcept = default;
};

#include "symbol.inl"
