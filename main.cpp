#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <type_traits>
#include <string>
using namespace std;

#define STATIC_ASSERT_EQ(expected, actual) \
   static_assert(std::is_same<expected, actual>::value, #expected "!=" #actual)

#include "argparse.hpp"


TEST_CASE("regular use", "[argument]")
{
   argparse::argument<int> a = argparse::arg<int>("hoge", 'h', "short description");

   STATIC_ASSERT_EQ(decltype(a)::arg_type, int);

   REQUIRE(a.name() == "hoge");
   REQUIRE(a.has_short_name());
   REQUIRE(a.short_name() == 'h');
   REQUIRE(a.help() == "short description");
}

TEST_CASE("omit short_name", "[argument]")
{
   argparse::argument<int> a = argparse::arg<int>("hoge", "desc");

   REQUIRE(!a.has_short_name());
   REQUIRE_THROWS(a.short_name());
}


TEST_CASE("make parser", "[parser]")
{
   argparse::parser<argparse::argument<int>, argparse::argument<string>>
      p = argparse::make_parser(
         argparse::arg<int>("hoge"),
         argparse::arg<string>("fuga", 'f')
      );

   SECTION("parse") {
      p.parse({ "progname", "--hoge", "10", "aaa", "-f", "foo", "bb", "cc" });

      REQUIRE(p.progname() == "progname");

      tuple<int, string> const& options = p.options();
      REQUIRE(std::get<0>(options) == 10);
      REQUIRE(std::get<1>(options) == "foo");

      vector<string> const& remains = p.remains();
      REQUIRE(remains[0] == "aaa");
      REQUIRE(remains[1] == "bb");
      REQUIRE(remains[2] == "cc");
   }
}
