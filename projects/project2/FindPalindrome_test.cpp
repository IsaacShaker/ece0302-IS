#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "FindPalindrome.hpp"

#include "catch.hpp"

// There should be at least one test per FindPalindrome method
TEST_CASE("test constructor", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.number() == 0);
}

TEST_CASE("test add", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
}

TEST_CASE("Test adding a non-allowable word", "[FindPalindrome]") {
    FindPalindrome b;
    // non alphabetical
    REQUIRE_FALSE(b.add("kayak1"));

    // already contained
    REQUIRE(b.add("a"));
    REQUIRE_FALSE(b.add("A"));

    // empty string
    REQUIRE_FALSE(b.add(""));
}

TEST_CASE("test add vector", "[FindPalindrome]") {
    FindPalindrome b;
    std::vector<std::string> words;
    words.push_back("a");
    words.push_back("AA");
    words.push_back("AaA");

    REQUIRE(b.add(words));
}

TEST_CASE("test add invalid vector", "[FindPalindrome]") {
    FindPalindrome b;
    std::vector<std::string> words;
    // repeat words
    words.push_back("a");
    words.push_back("A");

    REQUIRE_FALSE(b.add(words));
}

TEST_CASE("test isPalindrome", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.number() == 1);
}

TEST_CASE("test recursion", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.add("AA"));
    REQUIRE(b.add("AaA"));
    REQUIRE(b.number() == 6);
}

TEST_CASE("test number", "[FindPalindrome]") {
    FindPalindrome b;
    REQUIRE(b.number() == 0);

    REQUIRE(b.add("a"));
    REQUIRE(b.add("AA"));

    REQUIRE(b.number() == 2);
}

TEST_CASE("test clear", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.number() == 1);

    b.clear();
    // no more palindromes
    REQUIRE(b.number() == 0);
    // should be able to add "a" since it got removed
    REQUIRE(b.add("a"));
}

TEST_CASE("test toVector", "[FindPalindrome]") {
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.toVector()[0][0] == "a");
}

TEST_CASE("test cutTest1", "[FindPalindrome]") {
    FindPalindrome b;
    std::vector<std::string> words;
    // invalid - even number of characters with one odd value
    words.push_back("a");
    words.push_back("Aa");
    words.push_back("b");

    REQUIRE_FALSE(b.cutTest1(words));

    // valid - odd number of characters with one odd value
    words.push_back("Aaa");
    REQUIRE(b.cutTest1(words));
}

TEST_CASE("test cutTest2", "[FindPalindrome]") {
    FindPalindrome b;

    std::vector<std::string> words1, words2;
    // smaller sentence
    words1.push_back("a");
    words1.push_back("Aa");
    words1.push_back("b");

    // larger sentence
    words2.push_back("a");
    words2.push_back("Aa");
    words2.push_back("AaA");
    words2.push_back("b");

    // function should be able to distinguish between smaller and larger word
    REQUIRE(b.cutTest2(words1, words2));
    REQUIRE(b.cutTest2(words2, words1));

    // add a letter that is not contained in the larger vector
    words1.push_back("c");
    REQUIRE_FALSE(b.cutTest2(words1, words2));
    REQUIRE_FALSE(b.cutTest2(words2, words1));
}