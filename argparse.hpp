#pragma once

#include <string>
#include <vector>
#include <tuple>

namespace argparse {

template <typename T>
struct argument {
   using arg_type = T;

   argument(std::string const& name,
            char short_name,
            std::string const& help)
      : name_(name)
      , short_name_(short_name)
      , help_(help)
   {
   }

   std::string const& name() const {
      return name_;
   }

   bool has_short_name() const {
      return short_name_ != '\0';
   }

   char short_name() const {
      if (!has_short_name())
         throw std::logic_error("no short name");
      return short_name_;
   }

   std::string const& help() const {
      return help_;
   }

private:
   std::string name_;
   char short_name_;
   std::string help_;
};

template <typename T>
inline argument<T> arg(std::string const& name,
                       char short_name = '\0',
                       std::string const& help = "")
{
   return argument<T>{ name, short_name, help };
}

template <typename T>
inline argument<T> arg(std::string const& name,
                       std::string const& help)
{
   return argument<T>{ name, '\0', help };
}

inline argument<void> flag(std::string const& name,
                           char short_name = '\0',
                           std::string const& help = "")
{
   return argument<void>{ name, short_name, help };
}

inline argument<void> flag(std::string const& name,
                           std::string const& help)
{
   return argument<void>{ name, '\0', help };
}


template <typename... Args>
struct parser
{
   parser(Args&&... args)
      : args_{ std::forward<Args>(args)... }
   {
   }

   void parse(std::vector<std::string> const& args) {
      if (args.empty())
         throw std::runtime_error("argument must be at least one item(s).");

      prog_name_ = args[0];
      remains_.assign(args.begin() + 1, args.end());
   }

private:
   std::string prog_name_;
   std::tuple<typename Args::arg_type...> options_;
   std::vector<std::string> remains_;

   std::tuple<Args...> args_;
};

template <typename... Args>
parser<Args...> make_parser(Args&&... args) {
   return parser<Args...>{ std::forward<Args>(args)... };
}

} // namespace argparse;
