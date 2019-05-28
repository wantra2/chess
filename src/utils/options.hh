#pragma once

#include <boost/program_options.hpp>

namespace utils
{
    namespace po = boost::program_options;
    po::variables_map*
    parse_options(int argc, char* argv[]);
}
