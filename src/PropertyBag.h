#pragma once
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename TKey, typename TProperty>
class PropertyBag
{
  public:
    class Property
    {
      public:
        Property(const TProperty& property, bool compare = true)
            : m_property(property)
            , m_compare(compare)
        {}

        bool operator==(const Property& other) const
        {
            return ((m_compare == other.m_compare) && (m_property == other.m_property));
        }

        bool operator!=(const Property& other) const
        {
            return not(*this == other);
        }

        const TProperty& property() const
        {
            return m_property;
        }

        bool isCompare() const
        {
            return m_compare;
        }

      private:
        const TProperty m_property;
        bool m_compare;
    };

  public:
    using KeyPropertyPairType = std::pair<const TKey, Property>;
    using MapType = std::map<const TKey, Property>;

    PropertyBag() = default;
    PropertyBag(std::initializer_list<KeyPropertyPairType> list);
    ~PropertyBag() = default;

    bool operator==(const PropertyBag& other) const;
    bool operator!=(const PropertyBag& other) const;

    void insert(std::initializer_list<KeyPropertyPairType> list);
    const MapType& properties() const;

  private:
    std::vector<KeyPropertyPairType> uniqueElements(const PropertyBag& other) const;

  private:
    MapType m_properties;
};

template <typename TKey>
using StringPropertyBag = PropertyBag<TKey, std::string>;

template <typename TKey, typename TProperty>
PropertyBag<TKey, TProperty>::PropertyBag(std::initializer_list<KeyPropertyPairType> list)
    : m_properties(list)
{}

template <typename TKey, typename TProperty>
void PropertyBag<TKey, TProperty>::insert(std::initializer_list<KeyPropertyPairType> list)
{
    m_properties.insert(list);
}

template <typename TKey, typename TProperty>
bool PropertyBag<TKey, TProperty>::operator==(const PropertyBag& other) const
{
    for (const auto& [key, value] : m_properties)
    {
        if (other.m_properties.find(key) != other.m_properties.end())
        {
            const auto& this_prop = m_properties.at(key);
            const auto& other_prop = other.m_properties.at(key);

            if (this_prop.isCompare() != other_prop.isCompare())
            {
                return false;
            }

            if (this_prop.isCompare() && other_prop.isCompare())
            {
                if (this_prop.property() != other_prop.property())
                {
                    return false;
                }
            }
        }
    }

    const auto uniques = uniqueElements(other);
    for (const auto& item : uniques)
    {
        if (item.second.isCompare() == true)
        {
            return false;
        }
    }

    return true;
}

template <typename TKey, typename TProperty>
bool PropertyBag<TKey, TProperty>::operator!=(const PropertyBag& other) const
{
    return not(*this == other);
}

template <typename TKey, typename TProperty>
const typename PropertyBag<TKey, TProperty>::MapType& PropertyBag<TKey, TProperty>::properties() const
{
    return m_properties;
}

template <typename TKey, typename TProperty>
std::vector<typename PropertyBag<TKey, TProperty>::KeyPropertyPairType> PropertyBag<
    TKey, TProperty>::uniqueElements(const PropertyBag& other) const
{
    std::vector<KeyPropertyPairType> ret;

    for (const auto& [key, value] : m_properties)
    {
        if (other.m_properties.find(key) == other.m_properties.end())
        {
            ret.push_back({key, value});
        }
    }

    for (const auto& [key, value] : other.m_properties)
    {
        if (m_properties.find(key) == m_properties.end())
        {
            ret.push_back({key, value});
        }
    }

    return ret;
}
