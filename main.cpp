#include "argparse.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    auto parser = argparse::make_parser(
        argparse::arg<bool>("--hoge", "some argument"),
        argparse::arg<int> ("--fuga", "some argument")
    );

    parser.parse(argc, argv);

    decltype(parser)::args_type args;
    std::vector<std::string> remains;
    std::tie(args, remains) = parser.parsed();

    argparse::range_reader<float> range(0, 10);
    std::cout << std::boolalpha << range(10) << std::endl;
}
