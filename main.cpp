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

   using parser_t = argparse::parser<
      argparse::argument<int>,
      argparse::argument<string>
   >;
   parser_t p = argparse::make_parser(
      arg<int>   ("hoge"),
      arg<string>("fuga", 'f')
   );

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
