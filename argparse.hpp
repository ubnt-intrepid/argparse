///
/// Copyright (c) 2015 Yusuke Sasaki
///
/// This software is released under the MIT License.
/// See http://opensource.org/licenses/mit-license.php
/// or <LICENSE>.
///

#pragma once

#include <tuple>
#include <string>
#include <vector>

namespace argparse {

template <typename... Args>
class parser
{
public:
    using args_type = std::tuple<typename Args::arg_type...>;

    parser(Args&&... args)
        : arguments{std::forward<Args>(args)...}
    {
    }

    void parse(int argc, char const* argv[])
    {
    }

    std::tuple<args_type, std::vector<std::string>> parsed() const {
        return std::tuple<args_type, std::vector<std::string>>();
    }

private:
    // arguments.
    std::tuple<Args...> arguments;

    // parsed results
    args_type parsed_args;
    std::vector<std::string> remains_;
    std::string prog_name;
};

template <typename T>
class argument {
public:
    using arg_type = T;

    argument(std::string const& name, std::string const& description)
        : name(name), description(description)
    {
    }
private:
    std::string name;
    std::string description;
};

template <typename... Args>
parser<Args...> make_parser(Args&&... args)
{
    return parser<Args...>{std::forward<Args>(args)...};
}

template <typename T = bool>
argument<T> arg(std::string const& name, std::string const& description) {
    return argument<T>(name, description);
}

} // namespace argparse;
