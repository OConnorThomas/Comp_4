// Copyright 2023 Thomas O'Connor
#include "RandWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define TESTING_ITEM "gagggagaggcgagaaa"
using std::invalid_argument;
using std::out_of_range;

BOOST_AUTO_TEST_CASE(testOrderK) {
  RandWriter l(TESTING_ITEM, 3);
  BOOST_REQUIRE_EQUAL(l.orderK(), 3);
  RandWriter m(TESTING_ITEM, 0);
  BOOST_REQUIRE_EQUAL(m.orderK(), 0);
  RandWriter n(TESTING_ITEM, 100);
  BOOST_REQUIRE_EQUAL(n.orderK(), 100);
}

BOOST_AUTO_TEST_CASE(testFreqKGram) {
  RandWriter l(TESTING_ITEM, 4);
  BOOST_REQUIRE_EQUAL(l.freq("gagg"), 2);
  BOOST_REQUIRE_NO_THROW(l.freq("gagg"));
  BOOST_REQUIRE_THROW(l.freq("gag"), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq("gaggg"), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq(" "), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq(""), invalid_argument);
  RandWriter m(TESTING_ITEM, 1);
  BOOST_REQUIRE_EQUAL(m.freq("c"), 1);
  BOOST_REQUIRE_EQUAL(m.freq("g"), 9);
  BOOST_REQUIRE_EQUAL(m.freq("a"), 7);
  BOOST_REQUIRE_THROW(m.freq(" "), out_of_range);
}

BOOST_AUTO_TEST_CASE(testFreqKGramC) {
  RandWriter l(TESTING_ITEM, 4);
  BOOST_REQUIRE_EQUAL(l.freq("gagg", 'c'), 1);
  BOOST_REQUIRE_NO_THROW(l.freq("gagg", 'c'));
  BOOST_REQUIRE_THROW(l.freq("gag", 'a'), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq("gaggg", 'a'), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq(" ", 'a'), invalid_argument);
  BOOST_REQUIRE_THROW(l.freq("", 'a'), invalid_argument);
  RandWriter m(TESTING_ITEM, 1);
  BOOST_REQUIRE_EQUAL(m.freq("c", 'g'), 1);
  BOOST_REQUIRE_EQUAL(m.freq("g", 'a'), 5);
  BOOST_REQUIRE_EQUAL(m.freq("a", 'g'), 5);
  BOOST_REQUIRE_NO_THROW(m.freq("c", 'g'));
  BOOST_REQUIRE_NO_THROW(m.freq("g", 'a'));
  BOOST_REQUIRE_NO_THROW(m.freq("a", 'g'));
  BOOST_REQUIRE_THROW(m.freq(" ", 'a'), out_of_range);
  RandWriter n(TESTING_ITEM, 0);
  BOOST_REQUIRE_EQUAL(n.freq("", 'c'), 1);
  BOOST_REQUIRE_EQUAL(n.freq("", 'g'), 9);
  BOOST_REQUIRE_EQUAL(n.freq("", 'a'), 7);
}

BOOST_AUTO_TEST_CASE(testKRand) {
  RandWriter l(TESTING_ITEM, 6);
  BOOST_REQUIRE_EQUAL(l.kRand("gagagg"), 'c');
  BOOST_REQUIRE_NO_THROW(l.kRand("gagagg"));
  BOOST_REQUIRE_THROW(l.kRand("gag"), invalid_argument);
  BOOST_REQUIRE_THROW(l.kRand("gggggg"), out_of_range);
  RandWriter m(TESTING_ITEM, 2);
  BOOST_REQUIRE_EQUAL(m.kRand("cg"), 'a');
  BOOST_REQUIRE_NO_THROW(m.kRand("cg"));
  BOOST_REQUIRE_THROW(m.kRand("gag"), invalid_argument);
  BOOST_REQUIRE_THROW(m.kRand("cc"), out_of_range);
}

BOOST_AUTO_TEST_CASE(testGenerate) {
  RandWriter l(TESTING_ITEM, 3);
  BOOST_REQUIRE_THROW(l.generate("gagagg", 4), invalid_argument);
  BOOST_REQUIRE_NO_THROW(l.generate("gag", 4));
  BOOST_REQUIRE_THROW(l.generate("ccc", 4), out_of_range);
  RandWriter m(TESTING_ITEM, 0);
  BOOST_REQUIRE_THROW(m.generate("cg", 4), invalid_argument);
  BOOST_REQUIRE_NO_THROW(m.generate("", 4));
}
