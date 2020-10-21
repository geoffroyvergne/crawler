#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef REST
#define REST

//#pragma once
class Rest {
    public:
        int connect(std::string address, int port);
    private:
        static boost::property_tree::ptree parseBody(std::string body);
        static std::string jsonToString(boost::property_tree::ptree json);
};

#endif
