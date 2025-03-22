#pragma once
#include <string>
#include "utilite/dataStruct.h"

using namespace DATASTRUCT;

namespace UTILITY{

    struct NumberParser{

        //returns a list of float found in the string
        static List<float>* parse(std::string l);

    };

    struct ManifestParser{

        static List<std::string>* parse(std::string l);
    };

}