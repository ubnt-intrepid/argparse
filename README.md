Yet another command line parser for C++11
=========================================

* only one header file
* static type check

# Example (Work in Progress)

```cpp
#include "argparse.hpp"
using namespace std;

int main(int argc, char const* argv[])
{
   using argparse::arg;
   using argparse::flag;

   // construct a command line parser
   auto p = argparse::make_parser(

      // 1: option name  (string)
      // 2: short option (char)
      // 3: description  (string)
      arg<string>("ip", 'i', "IP address"),

      // without short name
      arg<short>("port", "port number of address"),

      // store true if '--verbose' (or '-v') is given
      flag("verbose", 'v', "show generated URL")
   );

   // parse arguments
   //   * show usage and exit with 0 if '-h' or '--help' are given.
   //   * show error message and exit if invalid arguments are given.
   //   * if the option `--from-file=<FILE>` (or '--from-file <FILE>') is given,
   //     read options from <FILE> (arguments are separated by new line)
   p.parse(argc, argv);

   // get parsed options and remaining arguments.
   string ip;
   short port;
   bool verbose;
   tie(ip, port, verbose) = p.args();
   vector<string> remains = p.remains();
}
```

# License
Copyright (c) 2015 Yusuke Sasaki

This software is released under the MIT License, see [LICENSE](LICENSE).
