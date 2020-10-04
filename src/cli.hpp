#include <boost/program_options.hpp>

namespace po = boost::program_options;

void getVersion();
void getHelp(po::options_description &desc);
void initCli(int argc, char** argv);
