#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

#include <ini.hpp>

Ini::Ini(std::string file) {
    try {
        boost::property_tree::ptree propertyTree;
        boost::property_tree::ini_parser::read_ini(file, propertyTree);
    
        this->propertyTree = propertyTree;
    } catch(std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "error: " << e.what();
        exit(EXIT_FAILURE);
    } catch(...) {
        BOOST_LOG_TRIVIAL(error) << "Exception of unknown type!";
        exit(EXIT_FAILURE);
    }
}

boost::property_tree::ptree Ini::getPtree() {
    return this->propertyTree;
}

void Ini::getIniValues() {
    boost::property_tree::ptree propertyTree = this->getPtree();

    if(!this->propertyTree.empty()) {
        //std::cout << "Test.testValue1 : " << propertyTree.get<std::string>("Test.testValue1") << std::endl;
        //std::cout << "Test.testValue2 : " << propertyTree.get<std::string>("Test.testValue2") << std::endl;
    }
}
