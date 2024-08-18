#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "PropertyBag.h"

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareDefault)
{
    const std::string s{"eins"};
    const bool expected_compare{true};

    // given a default initialized Property
    StringPropertyBag<int>::Property p1{s};

    // then the property is constructed properly
    EXPECT_EQ(p1.property(), s);
    EXPECT_EQ(p1.isCompare(), expected_compare);
}

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareExplicitTrue)
{
    // given a Property
    const std::string s{"eins"};
    const bool isCompare{true};

    // when a Property is created with isCompare explicit false
    StringPropertyBag<int>::Property p1{s, isCompare};

    // then the property is constructed properly
    EXPECT_EQ(p1.property(), s);
    EXPECT_EQ(p1.isCompare(), isCompare);
}

// PropertyBag::Property construction
TEST(PropertyBagProperty, CtorWithCompareExplicitFalse)
{
    // given a Property
    const std::string s{"eins"};
    const bool isCompare{false};

    // when a Property is created with isCompare explicit false
    StringPropertyBag<int>::Property p1{s, isCompare};

    // then the property is constructed properly
    EXPECT_EQ(p1.property(), s);
    EXPECT_EQ(p1.isCompare(), isCompare);
}

// PropertyBag::Property equality
TEST(PropertyBagProperty, CompareEqual)
{
    {
        // given two equal Properties with isCompare default true
        const auto s1{"eins"};
        const auto s2{"eins"};
        StringPropertyBag<int>::Property p1{s1};
        StringPropertyBag<int>::Property p2{s2};

        // then the properties isCompare equal
        EXPECT_TRUE(p1 == p2);
        EXPECT_TRUE(p2 == p1);
    }

    {
        // given two equal Properties with isCompare explicit false
        const std::string s1{"eins"};
        const std::string s2{"eins"};
        const bool isCompare{true};
        StringPropertyBag<int>::Property p1{s1, isCompare};
        StringPropertyBag<int>::Property p2{s2, isCompare};

        // then the properties isCompare equal
        EXPECT_TRUE(p1 == p2);
        EXPECT_TRUE(p2 == p1);
    }

    {
        // given two equal Properties with isCompare explicit false
        const std::string s1{"eins"};
        const std::string s2{"eins"};
        const bool isCompare{false};
        StringPropertyBag<int>::Property p1{s1, isCompare};
        StringPropertyBag<int>::Property p2{s2, isCompare};

        // then the properties isCompare equal
        EXPECT_TRUE(p1 == p2);
        EXPECT_TRUE(p2 == p1);
    }

    {
        // given two equal Properties with unequal isCompare
        const std::string s1{"eins"};
        const std::string s2{"eins"};
        const bool compare_s1{true};
        const bool compare_s2{false};
        StringPropertyBag<int>::Property p1{s1, compare_s1};
        StringPropertyBag<int>::Property p2{s2, compare_s2};

        // then the properties isCompare NOT equal
        EXPECT_FALSE(p1 == p2);
        EXPECT_FALSE(p2 == p1);
    }
}

// PropertyBag::Property inequality
TEST(PropertyBagProperty, CompareUnequal)
{
    {
        // given two unequal Properties with both isCompare default true
        const auto s1{"eins"};
        const auto s2{"zwei"};
        StringPropertyBag<int>::Property p1{s1};
        StringPropertyBag<int>::Property p2{s2};

        // then the properties isCompare unequal
        EXPECT_TRUE(p1 != p2);
        EXPECT_TRUE(p2 != p1);
    }

    {
        // given two unequal Properties with both isCompare explicit true
        const auto s1{"eins"};
        const auto s2{"zwei"};
        const bool isCompare{true};
        StringPropertyBag<int>::Property p1{s1, isCompare};
        StringPropertyBag<int>::Property p2{s2, isCompare};

        // then the properties isCompare unequal
        EXPECT_TRUE(p1 != p2);
        EXPECT_TRUE(p2 != p1);
    }

    {
        // given two unequal Properties with both isCompare explicit false
        const auto s1{"eins"};
        const auto s2{"zwei"};
        const bool isCompare{false};
        StringPropertyBag<int>::Property p1{s1, isCompare};
        StringPropertyBag<int>::Property p2{s2, isCompare};

        // then the properties isCompare unequal
        EXPECT_TRUE(p1 != p2);
        EXPECT_TRUE(p2 != p1);
    }

    {
        // given two equal Properties with different isCompare
        const auto s1{"eins"};
        const auto s2{"eins"};
        const bool compare_s1{true};
        const bool compare_s2{false};
        StringPropertyBag<int>::Property p1{s1, compare_s1};
        StringPropertyBag<int>::Property p2{s2, compare_s2};

        ASSERT_TRUE(s1 == s2);
        ASSERT_TRUE(compare_s1 != compare_s2);

        // then the properties isCompare unequal
        EXPECT_TRUE(p1 != p2);
        EXPECT_TRUE(p2 != p1);
    }
}

// PropertyBag construction def<ult
TEST(PropertyBag, DefaultConstruction)
{
    // given a default constructed PropertyBag
    PropertyBag<int, std::string> pb;

    // then PropertyBag is empty
    EXPECT_TRUE(pb.properties().empty() == true);
}

// PropertyBag construction from initializer list
TEST(PropertyBag, ConstructionFromInitializerList)
{
    // prepare initial items
    using KeyValue = PropertyBag<int, std::string>::KeyPropertyPairType;
    KeyValue kv1({1, {"eins"}});
    KeyValue kv2({2, {"zwei"}});
    KeyValue kv3({3, {"drei"}});
    std::vector<KeyValue> expected_items{kv1, kv2, kv3};

    // given a initializer list constructed PropertyBag
    PropertyBag<int, std::string> pb1({kv1, kv2, kv3});

    // then the PropertyBag is initialized as given
    EXPECT_TRUE(pb1.properties().size() == expected_items.size());
    for (const auto& item : expected_items)
    {
        EXPECT_TRUE(pb1.properties().at(item.first) == item.second);
    }
}

// PropertyBag element insertion
TEST(PropertyBag, ItemInsertion)
{
    // prepare initial items
    using KeyValue = PropertyBag<int, std::string>::KeyPropertyPairType;
    KeyValue kv1({1, {"eins"}});
    KeyValue kv2({2, {"zwei"}});
    KeyValue kv3({3, {"drei"}});
    std::vector<KeyValue> init_items{kv1, kv2, kv3};

    // prepare items to insert
    KeyValue kv4({4, {"vier"}});
    KeyValue kv5({5, {"fuenf"}});
    KeyValue kv6({6, {"sechs"}});
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