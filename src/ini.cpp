#include <iostream>
#include <boost/program_options.hpp>

#include <ini.hpp>

Ini::Ini(std::string configFile) {
    try {
        boost::property_tree::ptree propertyTree;
        boost::property_tree::ini_parser::read_ini(configFile, propertyTree);
        
        this->propertyTree = propertyTree;
    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }
}

boost::property_tree::ptree Ini::getPtree() {
    return this->propertyTree;
}

void Ini::getIniValues() {
    boost::property_tree::ptree propertyTree = this->getPtree();

    if(!this->propertyTree.empty()) {
        std::cout << "Test.testValue1 : " << propertyTree.get<std::string>("Test.testValue1") << std::endl;
        std::cout << "Test.testValue2 : " << propertyTree.get<std::string>("Test.testValue2") << std::endl;
    }
}
