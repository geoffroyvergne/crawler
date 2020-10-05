#include <boost/property_tree/ini_parser.hpp>

class Ini {
    public:
        Ini();
        Ini(std::string configFile);
        boost::property_tree::ptree getPtree();
        void getIniValues();
    private:
        boost::property_tree::ptree propertyTree;
};
