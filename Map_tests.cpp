// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "unit_test_framework.h"

using std::pair;
using std::string;
using std::vector;

TEST(map_public_test) {
    Map<string, double> words;
    words["hello"] = 1;
    pair<string, double> tuple;
    tuple.first = "world";
    tuple.second = 2;
    words.insert(tuple);
    words.insert({ "pi", 3.14159 });

    vector<string> expected_keys = { "hello", "pi", "world" };
    vector<double> expected_values = { 1, 3.14159, 2 };
    vector<string> actual_keys;
    vector<double> actual_values;

    for (auto& p : words) {
        auto word = p.first; //key
        auto number = p.second; //value
        actual_keys.push_back(word);
        actual_values.push_back(number);
    }
    ASSERT_EQUAL(expected_keys, actual_keys);
    ASSERT_EQUAL(expected_values, actual_values);

    // Check if a key is in the map.  find() returns an iterator.
    auto found_it = words.find("pi");
    ASSERT_NOT_EQUAL(found_it, words.end());
    auto& word = (*found_it).first; //key
    auto number = (*found_it).second; //value
    ASSERT_EQUAL(word, "pi");
    ASSERT_ALMOST_EQUAL(number, 3.14159, 0.00001);

    // When using the [] notation. An element not found is automatically created.
    // If the value type of the map is numeric, it will always be 0 "by default".
    ASSERT_EQUAL(words["bleh"], 0.0);
}

TEST(test_empty)
{
    Map<string, int> words;
    ASSERT_TRUE(words.empty());
    words.insert({ "hello", 2 });
    ASSERT_FALSE(words.empty());
}

TEST(test_size)
{
    Map<string, int> words;
    ASSERT_EQUAL(words.size(), 0);
    words.insert({ "hello", 2 });
    words.insert({ "hey", 4 });
    words.insert({ "sup", 3 });
    ASSERT_EQUAL(words.size(), 3);
}

TEST(test_find)
{
    Map<string, int> words;
    words.insert({ "sup", 3 });
    words.insert({ "hey", 4 });
    ASSERT_EQUAL( words.find("sup"), words.begin());
    assert(words.find("dog") != words.end());
    ASSERT_EQUAL(words.find("dog"), words.end());
}

TEST(test_insert)
{
   
    
}

TEST(test_operator)
{
    Map<string, int> words;
    words.insert({ "sup", 3 });
    words.insert({ "hello", 2 });
    words.insert({ "hey", 4 });
    ASSERT_EQUAL(words["sup"], 3);
    ASSERT_EQUAL(words["hello"], 2);
}

TEST_MAIN()
