///
/// Copyright (c) 2015 Yusuke Sasaki
///
/// This software is released under the MIT License.
/// See http://opensource.org/licenses/mit-license.php
/// or <LICENSE>.
///

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <tuple>


namespace argparse {

template <typename T>
class default_reader {
  public:
    bool operator()(T const&) const { return true; }
};

template <typename T>
class oneof_reader {
    std::vector<T> vals;
  public:
    oneof_reader(std::initializer_list<T> v) : vals(v) {}
    bool operator()(T const& v) const {
        return std::find(vals.begin(), vals.end(), v) != vals.end();
    }
};

template <typename... Args>
oneof_reader<typename std::common_type<Args...>::type> oneof(Args... args) {
    return oneof_reader<typename std::common_type<Args...>::type>{ std::forward<Args>(args)... };
}

template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class range_reader {
    T low, high;
  public:
    range_reader(T low, T high) : low(low), high(high) {}

    bool operator()(T const& v) const { return low <= v && v < high; }
};

template <typename T>
range_reader<T> range(T low, T high) {
    return range_reader<T>{low, high};
}

template <typename T, typename Reader = default_reader<T>>
class argument {
  public:
    using arg_type = T;
    argument(std::string const& name, std::string const& description, Reader reader = Reader())
        : name(name), description(description), reader(reader) {}
  private:
    std::string name;
    std::string description;
    Reader reader;
};

template <typename T>
argument<T> arg(std::string const& name, std::string const& description) {
    return argument<T>(name, description);
}

template <typename T>
argument<T, range_reader<T>> arg(std::string const& name, std::string const& description,
                                 range_reader<T> reader) {
    return argument<T, range_reader<T>>(name, description);
}

template <typename T>
argument<T, oneof_reader<T>> arg(std::string const& name, std::string const& description,
                                 oneof_reader<T> reader) {
    return argument<T, oneof_reader<T>>(name, description, reader);
}

template <typename... Args>
class parser {
  public:
    using args_type = std::tuple<typename Args::arg_type...>;
    parser(Args&&... args): arguments{std::forward<Args>(args)...} {}
    void parse(int argc, char const* argv[]) {}
    std::tuple<args_type, std::vector<std::string>> parsed() const {
        return std::tuple<args_type, std::vector<std::string>>();
    }
  private:
    std::tuple<Args...> arguments;
    args_type parsed_args;
    std::vector<std::string> remains_;
    std::string prog_name;
};

template <typename... Args>
parser<Args...> make_parser(Args&&... args) {
    return parser<Args...>{std::forward<Args>(args)...};
}

} // namespace argparse;
