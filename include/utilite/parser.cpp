#include "parser.h"

namespace UTILITY{
    List<float>* NumberParser::parse(std::string l){
        bool is_current = false;
        int index = 0;
        int size = 1;
        bool is_decimal = 0;


        DynamicList<float> *liste = new DynamicList<float>();
        if (!l.size()) return dynamic_cast<List<float>*> (liste);
        int i = 0;

        for (char& x:l){
            

            if(!is_current && (std::isdigit(x) || x =='-')) {
                index = i;
                size = 1;
                is_current = true;

            }

            else if (std::isdigit(x)) size++;

            else if (x=='.' && !is_decimal){
                is_decimal = true;
                size++;
            }
            else if(is_current){
                if(is_decimal){
                    liste->append(std::stof(l.substr(index, size)));
                }
                else {
                    liste->append(std::stoi(l.substr(index, size)));
                }
                is_current = false;
                is_decimal = false;

            }
            

            i++;

        } 
        if(is_current){
            if(is_decimal){
                liste->append(std::stof(l.substr(index, size)));
            }
            else {
                liste->append(std::stoi(l.substr(index, size)));
            }

        }

        return liste;
    }
}