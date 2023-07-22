#pragma once

#include "Lexer.hpp"
#include <string>
#include <algorithm>

void RemoveCharacter(std::string* strToRemove, char charToRemove)
{
    strToRemove->erase(remove(strToRemove->begin(), strToRemove->end(), charToRemove), strToRemove->end());
}

namespace strc{
    class Parser
    {
    private:
        std::vector<strc::INT*> ints;
        std::vector<strc::FLOAT*> floats;
        std::vector<strc::STRING*> strings;
        std::vector<std::string>& identifiers;
        Lexer lex;
        Logger log;
    public:
        Parser(std::string file_name): lex(file_name), identifiers(lex.GetIdentifiers()){}
        ~Parser()
        {
            for(size_t i = 0; i < ints.size(); i++)
            {
                delete ints[i];
            }

            for(size_t i = 0; i < floats.size(); i++)
            {
                delete floats[i];
            }

            for(size_t i = 0; i < strings.size(); i++)
            {
                delete strings[i];
            }
        }

        

        void CheckInts(int i)
        {
            if(identifiers[i] == "int")
            {
                if(identifiers[i + 2] == ":")
                {
                    ints.push_back(new INT(strc::MakeInt(std::stoi(identifiers[i + 3]), identifiers[i + 1])));
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }

                if(ints[i]->value > 2147483647)
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
                    floats.push_back(new FLOAT(strc::MakeFloat(std::stof(identifiers[i + 3]), identifiers[i + 1])));
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        void CheckStrings(int i)
        {
            int iterator = 0;
            if(identifiers[i] == "string")
            {
                if(identifiers[i + 2] == ":")
                {
                    std::string quoteCheck = identifiers[i + 3].substr(0, 1);
                    if(quoteCheck == "\"")
                    {
                        RemoveCharacter(&identifiers[i + 3], '\"');
                        std::string temp = identifiers[i + 3];
                        
                        while(identifiers[i + 3 + iterator].back() != '\"')
                        {
                            temp += " " + identifiers[i + 3 + iterator + 1];
                            RemoveCharacter(&temp, '\"');
                            iterator++;
                        }
                        
                        strings.push_back(new STRING(strc::MakeString(temp, identifiers[i + 1])));
                    }
                }
                else
                {   
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        std::vector<strc::INT*> GetInts()
        {
            return ints;
        }

        std::vector<strc::FLOAT*> GetFloats()
        {
            return floats;
        }

        std::vector<strc::STRING*> GetStrings()
        {
            return strings;
        }

        void PrintIdentifiers(){
            for(int i = 0; i < identifiers.size(); i++){
                std::cout << identifiers[i] << std::endl;
            }
        }

        std::vector<std::string>& GetIdentifiers()
        {
            return lex.GetIdentifiers();
        }

    };
}