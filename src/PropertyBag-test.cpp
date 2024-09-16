#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "PropertyBag.h"

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareDefault)
{
    const std::string name{"eins"};
    const bool expected{true};

    // given a default initialized Property
    StringPropertyBag<int>::Property prop{name};

    // then the property is constructed properly
    EXPECT_EQ(prop.property(), name);
    EXPECT_EQ(prop.isCompare(), expected);
}

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareExplicitTrue)
{
    // given a Property
    const std::string name{"eins"};
    const bool isCompare{true};

    // when a Property is created with isCompare explicit false
    StringPropertyBag<int>::Property prop{name, isCompare};

    // then the property is constructed properly
    EXPECT_EQ(prop.property(), name);
    EXPECT_EQ(prop.isCompare(), isCompare);
}

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareExplicitFalse)
{
    // given a Property
    const std::string name{"eins"};
    const bool isCompare{false};

    // when a Property is created with isCompare explicit false
    StringPropertyBag<int>::Property prop{name, isCompare};

    // then the property is constructed properly
    EXPECT_EQ(prop.property(), name);
    EXPECT_EQ(prop.isCompare(), isCompare);
}

// PropertyBag::Property equality
TEST(PropertyBagProperty, DefaultCompare)
{
    // given two equal Properties with isCompare default true
    const std::string name1{"eins"};
    const std::string name2{"eins"};
    StringPropertyBag<int>::Property prop1{name1};
    StringPropertyBag<int>::Property prop2{name2};

    // then the properties isCompare equal
    EXPECT_TRUE(prop1 == prop2);
    EXPECT_TRUE(prop2 == prop1);
}

TEST(PropertyBagProperty, ExplicitCompareTrue)
{
    // given two equal Properties with isCompare explicit true
    const std::string name1{"eins"};
    const std::string name2{"eins"};
    const bool isCompare{true};
    StringPropertyBag<int>::Property prop1{name1, isCompare};
    StringPropertyBag<int>::Property prop2{name2, isCompare};

    // then the properties isCompare equal
    EXPECT_TRUE(prop1 == prop2);
    EXPECT_TRUE(prop2 == prop1);
}

TEST(PropertyBagProperty, ExplicitCompareFalse)
{
    // given two equal Properties with isCompare explicit false
    const std::string name1{"eins"};
    const std::string name2{"eins"};
    const bool isCompare{false};
    StringPropertyBag<int>::Property prop1{name1, isCompare};
    StringPropertyBag<int>::Property prop2{name2, isCompare};

    // then the properties isCompare equal
    EXPECT_TRUE(prop1 == prop2);
    EXPECT_TRUE(prop2 == prop1);
}

TEST(PropertyBagProperty, CompareInvariant)
{
    // given two equal Properties with unequal isCompare
    const std::string name1{"eins"};
    const std::string name2{"eins"};
    const bool compareName1{true};
    const bool compareName2{false};
    StringPropertyBag<int>::Property prop1{name1, compareName1};
    StringPropertyBag<int>::Property prop2{name2, compareName2};

    // then the properties isCompare NOT equal
    EXPECT_FALSE(prop1 == prop2);
    EXPECT_FALSE(prop2 == prop1);
}

// PropertyBag::Property inequality
TEST(PropertyBagProperty, OperatorUnequalWithDefaultCompare)

{
    // given two unequal Properties with both isCompare default true
    const std::string name1{"eins"};
    const std::string name2{"zwei"};
    StringPropertyBag<int>::Property prop1{name1};
    StringPropertyBag<int>::Property prop2{name2};

    // then the properties isCompare unequal
    EXPECT_TRUE(prop1 != prop2);
    EXPECT_TRUE(prop2 != prop1);
}

TEST(PropertyBagProperty, OperatorUnequalWithExplicitCompareTrue)
{
    // given two unequal Properties with both isCompare explicit true
    const std::string name1{"eins"};
    const std::string name2{"zwei"};
    const bool isCompare{true};
    StringPropertyBag<int>::Property prop1{name1, isCompare};
    StringPropertyBag<int>::Property prop2{name2, isCompare};

    // then the properties isCompare unequal
    EXPECT_TRUE(prop1 != prop2);
    EXPECT_TRUE(prop2 != prop1);
}

TEST(PropertyBagProperty, OperatorUnequalWithExplicitCompareFalse)
{
    // given two unequal Properties with both isCompare explicit false
    const std::string name1{"eins"};
    const std::string name2{"zwei"};
    const bool isCompare{false};
    StringPropertyBag<int>::Property prop1{name1, isCompare};
    StringPropertyBag<int>::Property prop2{name2, isCompare};

    // then the properties isCompare unequal
    EXPECT_TRUE(prop1 != prop2);
    EXPECT_TRUE(prop2 != prop1);
}

TEST(PropertyBagProperty, OperatorUnequalWithCompareInvariant)
{
    // given two equal Properties with different isCompare
    const std::string name1{"eins"};
    const std::string name2{"eins"};
    const bool compareName1{true};
    const bool compareName2{false};
    StringPropertyBag<int>::Property prop1{name1, compareName1};
    StringPropertyBag<int>::Property prop2{name2, compareName2};

    ASSERT_TRUE(name1 == name2);
    ASSERT_TRUE(compareName1 != compareName2);

    // then the properties isCompare unequal
    EXPECT_TRUE(prop1 != prop2);
    EXPECT_TRUE(prop2 != prop1);
}

// PropertyBag construction def<ult
TEST(PropertyBag, DefaultConstruction)
{
    // given a default constructed PropertyBag
    PropertyBag<int, std::string> propBag;

    // then PropertyBag is empty
    EXPECT_TRUE(propBag.properties().empty() == true);
}

// PropertyBag construction from initializer list
TEST(PropertyBag, ConstructionFromInitializerList)
{
    // prepare initial items
    using Property = PropertyBag<int, std::string>::Property;
    using KeyValue = PropertyBag<int, std::string>::KeyPropertyPairType;

    KeyValue kv1({1, Property("eins")});
    KeyValue kv2({2, Property("zwei")});
    KeyValue kv3({3, Property("drei")});
    std::vector<KeyValue> expected{kv1, kv2, kv3};

    // given a initializer list constructed PropertyBag
    PropertyBag<int, std::string> pb1({kv1, kv2, kv3});

    // then the PropertyBag is initialized as given
    EXPECT_TRUE(pb1.properties().size() == expected.size());
    for (const auto& item : expected)
    {
        EXPECT_TRUE(pb1.properties().at(item.first) == item.second);
    }
}

// PropertyBag element insertion
TEST(PropertyBag, ItemInsertion)
{
    // prepare initial items
    using Property = PropertyBag<int, std::string>::Property;
    using KeyValue = PropertyBag<int, std::string>::KeyPropertyPairType;

    KeyValue kv1({1, Property("eins")});
    KeyValue kv2({2, Property("zwei")});
    KeyValue kv3({3, Property("drei")});
    std::vector<KeyValue> init_items{kv1, kv2, kv3};

    // prepare items to insert
    KeyValue kv4({4, Property("vier")});
    KeyValue kv5({5, Property("fünf")});
    KeyValue kv6({6, Property("sechs")});
    std::vector<KeyValue> insert_items{kv4, kv5, kv6};

    // prepare complete set of items
    std::vector<KeyValue> expected_items(init_items);
    for (const auto& item : insert_items)
    {
        expected_items.push_back(item);
    }

    // given an intialized PropertyBag
    PropertyBag<int, std::string> pb1({kv1, kv2, kv3});

    // when items are inserted
    for (const auto& item : insert_items)
    {
        pb1.insert({item});
    }

    // then the PropertyBag contains all items
    EXPECT_TRUE(pb1.properties().size() == expected_items.size());
    for (const auto& item : expected_items)
    {
        EXPECT_TRUE(pb1.properties().at(item.first) == item.second);
    }
}