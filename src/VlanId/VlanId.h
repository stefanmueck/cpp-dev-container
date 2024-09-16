#pragma once
#include "ValueRange/ValueRange.h"
#include <cstdint>
#include <stdexcept>
#include <string>

static constexpr std::uint32_t VlanMinValue{0};
static constexpr std::uint32_t VlanMaxValue{4095};
using VlandDefaultRange = ValueRange<std::uint32_t, VlanMinValue, VlanMaxValue>;

template <class TValueRange = VlandDefaultRange>
class VlanId
{
    static_assert(IsValueRange<TValueRange>::value, "Template argument must be of type Range");

  public:
    using Id = typename TValueRange::ValueType;

    VlanId() = delete;
    ~VlanId() = default;

    explicit VlanId(Id vlanId)
        : m_id(vlanId)
    {
        if (not m_range.isInRange(vlanId))
        {
            throw std::out_of_range("VLAN-ID " + std::to_string(vlanId) + " is out of range (" +
                                    std::to_string(m_range.Min) + ", " + std::to_string(m_range.Max) + ")!");
        }
    }

    bool operator==(const VlanId& other) const { return (m_id == other.m_id); }
    bool operator!=(const VlanId& other) const { return not(*this == other); }
    bool operator<(const VlanId& other) const { return (m_id < other.m_id); }
    bool operator>(const VlanId& other) const { return (m_id > other.m_id); }

    Id value() const { return m_id; }

  private:
    TValueRange m_range;
    Id m_id;
};