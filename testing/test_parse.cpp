#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "utilite/parser.h"
#include <iostream>
#include <string>

using namespace UTILITY;

TEST_CASE("manifest parser", "[Parser]") {
    std::string l = "C:/Users/ORDI/Desktop/openGL/RessourceDirectory/mesh/teapot.obj obj a\n";
    std::cout << *ManifestParser::parse(l)<<std::endl;

    std::string n = "o 2.30 1/5/9.7 -4.86";
    std::cout << *NumberParser::parse(n)<<std::endl;
}