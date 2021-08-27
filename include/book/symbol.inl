#include "symbol.h"

inline Symbol::Symbol(int id, const char _name[8], const x2h::type::data::Exchange exchange) noexcept
    : id(id),
    exchange(exchange)
{
    std::memcpy(code, _name, sizeof(code));
}