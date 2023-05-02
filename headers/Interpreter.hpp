#pragma once

#include "Lexer.hpp"

namespace strc{
    class Interpreter
    {
    private:
        std::vector<strc::INT> ints;
        std::vector<strc::FLOAT> floats;
        std::vector<strc::STRING> strings;
        std::vector<std::string>& identifiers;
        Lexer lex;
        Logger log;
    public:
        Interpreter(std::string file_name) : lex(file_name), identifiers(lex.GetIdentifiers()){}
        ~Interpreter(){
        }

        void CheckInts(int i)
        {
            if(identifiers[i] == "int")
            {
                if(identifiers[i + 2] == ":")
                {
                    ints.push_back(strc::MakeInt(std::stoi(identifiers[i + 3]), identifiers[i + 1]));
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }

                if(ints[i].value > 2147483647)
                {
                    log.Error(std::string(identifiers[i] + " " + identifiers[i + 1]).c_str(), " is too large, program crashed");
                }
            }
        }

        void CheckFloats(int i)
        {
            if(identifiers[i] == "float")
            {
                if(identifiers[i + 2] == ":")
                {
                    floats.push_back(strc::MakeFloat(std::stof(identifiers[i + 3]), identifiers[i + 1]));
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        void CheckStrings(int i)
        {
            if(identifiers[i] == "string")
            {
                if(identifiers[i + 2] == ":")
                {
                    if(identifiers[i + 3] == "\"")
                    {
                        strings.push_back(strc::MakeString(identifiers[i + 3], identifiers[i + 1]));
                    }
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        void Print(int i)
        {
            if(identifiers[i] == "print")
            {
                if(identifiers[i + 1] == ":")
                {
                    for(int j = 0; j < ints.size(); j++)
                    {
                        if(identifiers[i + 2] == ints[j].name)
                        {
                            std::cout << ints[j].value << std::endl;
                        }
                    }

                    for(int j = 0; j < floats.size(); j++)
                    {
                        if(identifiers[i + 2] == floats[j].name)
                        {
                            std::cout << floats[j].value << std::endl;
                        }
                    }

                    for(int j = 0; j < strings.size(); j++)
                    {
                        if(identifiers[i + 2] == ints[j].name)
                        {
                            std::cout << strings[j].value << std::endl;
                        }
                    }
                }
                else{
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        void Run(){
            for(int i = 0; i < identifiers.size(); i++)
            {
                //std::cout << identifiers[i] << std::endl;
                CheckInts(i);
                CheckFloats(i);
                Print(i);
            }
        }
    };
    
}