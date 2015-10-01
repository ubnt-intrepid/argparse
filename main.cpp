#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


namespace argparse {

class parser
{
public:
    parser() = default;
    ~parser() = default;


    void parse(int argc, char const** argv)
    {
        prog_name_.assign(argv[0]);
        for (int i = 1; i < argc; ++i) {
            remains_.emplace_back(argv[i]);
        }
        short_options_['a'] = "hogehoge";
        long_options_["fuga"] = "foo";
    }

    void dump_result() const {
        std::cout << "Program name: " << prog_name_ << std::endl;

        std::cout << "short options: " << std::endl;
        for (auto& itm: short_options_) {
            std::cout << "  - " << itm.second << " (-" << itm.first << ")\n";
        }

        std::cout << "long options: " << std::endl;
        for (auto& itm: long_options_) {
            std::cout << "  - " << itm.second << " (--" << itm.first << ")\n";
        }

        std::cout << "Remaining arguments: " << std::endl;
        for (auto& itm: remains_) {
            std::cout << "  - " << itm << std::endl;
        }
    }
private:
    // parsed options
    std::string prog_name_;
    std::unordered_map<char, std::string>        short_options_;
    std::unordered_map<std::string, std::string> long_options_;
    std::vector<std::string>                     remains_;
};

} // namespace argparse;


int main(int argc, char const* argv[])
{
    argparse::parser parser;
    parser.parse(argc, argv);

    parser.dump_result();
}
