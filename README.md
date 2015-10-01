Yet another command line parser for C++11
=========================================

* only ONE header file
* statically type check (use valiadic template)

# Example (WIP)

```cpp
#include "argparse.hpp"
using namespace std;

int main(int argc, char const* argv[])
{
    // construct a command line parser
    auto p = argparse::make_parser(
        argparse::arg<bool>  ("--hoge", 'g', "some description"),
        argparse::arg<int>   ("--fuga",      "awesome options with value", 0),
        argparse::arg<string>("--foo",  'o', "hogehoge", argparse::oneof("a", "b", "c")),
        argparse::arg<double>("--maa",  'm', "range", argparse::range(0, 100)),
    );

    // ./a.exe --hoge --fuga=0 --foo b
    p.parse(argc, argv);

    decltype(p)::args_type args;    // :: tuple<bool, int, string>
    vector<string> remains;
    tie(args, remains) = p.parsed();
}
```

# License
Copyright (c) 2015 Yusuke Sasaki

This software is released under the MIT License, see [LICENSE](LICENSE).
