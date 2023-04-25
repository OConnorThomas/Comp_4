// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 5/12/2022

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStepInstr1) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testStepInstr2) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testStepInstr3) { // length_error - parameter length != 16
  BOOST_CHECK_THROW(FibLFSR l3(""), length_error);
  BOOST_CHECK_THROW(FibLFSR l3("1111"), length_error);
  BOOST_CHECK_THROW(FibLFSR l3("11111111111111111111"), length_error);
}

BOOST_AUTO_TEST_CASE(testStepInstr4) { // invalid_argument - parameter contains !1 && !0
  BOOST_REQUIRE_THROW(FibLFSR l4("1011011000110112"), invalid_argument);
  BOOST_REQUIRE_THROW(FibLFSR l4("101101100011011c"), invalid_argument);
}

BOOST_AUTO_TEST_CASE(testStepInstr5) { // Both length_error and invalid_argument
  BOOST_REQUIRE_THROW(FibLFSR l5("abcd"), length_error);
  BOOST_REQUIRE_THROW(FibLFSR l5("abcdabcdabcdabcdabcd"), length_error);
}