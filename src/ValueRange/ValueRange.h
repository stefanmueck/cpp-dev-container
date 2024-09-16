#pragma once
#include <cstdint>
#include <utility>

template <typename T_, T_ TMin, T_ TMax>
struct ValueRange
{
    static_assert(TMin <= TMax, "TMin must be less than or equal to TMax");

    using ValueType = T_;

    static constexpr T_ Min{TMin};
    static constexpr T_ Max{TMax};

    bool isInRange(const T_& value) const { return (value >= Min) && (value <= Max); }
};

template <typename T_>
struct IsValueRange : std::false_type
{};

template <typename T_, T_ TMin, T_ TMax>
struct IsValueRange<ValueRange<T_, TMin, TMax>> : std::true_type
{};