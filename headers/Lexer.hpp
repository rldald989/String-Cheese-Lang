#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "Logger.hpp"

namespace strc{

    struct INT
    {
        int value;
        std::string name;
    };

    INT MakeInt(int value, std::string name)
    {
        INT i = {value, name};
        return i;
    }

    struct FLOAT
    {
        float value;
        std::string name;
    };

    FLOAT MakeFloat(float value, std::string name)
    {
        FLOAT i = {value, name};
        return i;
    }

    struct STRING
    {
        std::string value;
        std::string name;
    };

    STRING MakeString(std::string value, std::string name)
    {
        STRING i = {value, name};
        return i;
    }

    class Lexer
    {
    private:
        std::vector<std::string> identifiers;
    public:
        Lexer(std::string file)
        {
            std::ifstream code;
            std::string temp;
            
            code.open(file);

            while(code >> temp >> std::ws)
            {
                if(temp == "\0"){

                }
                else{
                    identifiers.push_back(temp);
                }
            }

            code.close();
        }
        ~Lexer(){}

        std::vector<std::string>& GetIdentifiers()
        {
            return identifiers;
        }
    };
}