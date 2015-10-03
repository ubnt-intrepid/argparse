#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <type_traits>
#include <string>
using namespace std;

#define STATIC_ASSERT_EQ(expected, actual) \
   static_assert(std::is_same<expected, actual>::value, #expected "!=" #actual)

#include "argparse.hpp"

TEST_CASE("make parser", "[parser]")
{
   using argparse::arg;
   using argparse::flag;

   using parser_t = argparse::parser<
      argparse::argument_with_value<int>,
      argparse::argument_with_value<string>,
      argparse::argument_flag
   >;
   parser_t p = argparse::make_parser(
      arg<int>   ("hoge"),
      arg<string>("fuga", 'f'),
      flag("foo")
   );

   p.parse({ "progname", "--hoge", "10", "aaa", "-f", "foo", "bb", "cc", "--foo" });

   REQUIRE(p.progname() == "progname");

   tuple<int, string, bool> const& options = p.options();
   REQUIRE(std::get<0>(options) == 10);
   REQUIRE(std::get<1>(options) == "foo");
   REQUIRE(std::get<2>(options) == true);

   vector<string> const& remains = p.remains();
   REQUIRE(remains[0] == "aaa");
   REQUIRE(remains[1] == "bb");
   REQUIRE(remains[2] == "cc");
}
