#include "options.hh"

#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace utils
{

    po::variables_map*
    parse_options(int argc, char* argv[])
    {
        try
        {
            po::options_description desc("Allowed options");
            desc.add_options()
                ("help,h", "show usage")
                ("pgn", po::value<std::string>(), "path to the PGN game file")
                ("listeners,l", po::value<std::vector<std::string>>()->multitoken(), "list of paths to listnener plugins")
                ("perft", po::value<std::string>(), "path to a perft file");

            auto vm = new po::variables_map;
            po::store(po::parse_command_line(argc, argv, desc), *vm);

            po::notify(*vm);
            if (vm->count("help"))
            {
                std::cout << desc << std::endl;
                return nullptr;
            }
            return vm;

        }
        catch(std::exception& e)
        {
            std::cerr << "Incorrect arguments, try the option -h for help" << '\n';
            return nullptr;
        }

    }
}
