Yet another command line parser for C++11
=========================================

* only one header file
* static type check

# Example (Work in Progress)

```cpp
#include "argparse.hpp"
using namespace std;

enum class Hoge { A, B, C };
std::istream& operator>>(std::istream& is, Hoge& h)
{
   std::string src;
   is >> src;
   if      (src == "A") h = Hoge::A;
   else if (src == "B") h = Hoge::B;
   else if (src == "C") h = Hoge::C;
   else throw std::runtime_error("invalid characters");

   return is;
}

int main(int argc, char const* argv[])
{
   // construct a command line parser
   auto p = argparse::make_parser(
      argparse::arg<bool>  ("--hoge", 'g', "some description"),
      argparse::arg<int>   ("--fuga",      "awesome options with value", 0),
      argparse::arg<string>("--foo",  'o', "hogehoge", argparse::oneof("a", "b", "c")),
      argparse::arg<double>("--bar",  'm', "range",    argparse::range(0, 100)),
      argparse::arg<Hoge>  ("--hogehoge")
   );

   // parse arguments
   //   * show usage and exit with 0 if '-h' or '--help' are given.
   //   * show error message and exit if invalid arguments are given.
   //   * if the option `--from-file=<FILE>` (or '--from-file <FILE') is given,
   //     read options from <FILE> (arguments are separated by new line)
   p.parse(argc, argv);

   // get parsed options and remaining arguments.
   bool   hoge;
   int    fuga;
   string foo;
   double bar;
   Hoge   hogehoge;
   tie(hoge, fuga, foo, bar, hogehoge) = p.args();  // :: tuple<bool, int, string, double, Hoge>
   auto remains = p.remains();                      // :: vector<string>
}
```

# License
Copyright (c) 2015 Yusuke Sasaki

This software is released under the MIT License, see [LICENSE](LICENSE).
