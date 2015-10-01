#include "argparse.hpp"

int main(int argc, char const* argv[])
{
    auto parser = argparse::make_parser(
        argparse::arg     ("--hoge", "some argument"),
        argparse::arg<int>("--fuga", "some argument")
    );

    parser.parse(argc, argv);

    decltype(parser)::args_type args;
    std::vector<std::string> remains;
    std::tie(args, remains) = parser.parsed();
}
