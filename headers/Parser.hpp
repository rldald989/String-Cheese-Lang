#pragma once

#include "Lexer.hpp"
#include <string>
#include <algorithm>
#include <unordered_map>

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
        std::unordered_map<int, std::string> m_no_func;
        Lexer m_lexer;
    public:
        Parser(Lexer& lexer): m_lexer(lexer), identifiers(m_lexer.GetIdentifiers()){}
        ~Parser()
        {
            
        }

        void ReleaseData(){
            for(size_t i = 0; i < ints.size(); i++)
            {
                delete ints[i]->conv_value;
                delete ints[i];
            }

            for(size_t i = 0; i < floats.size(); i++)
            {
                delete floats[i]->conv_value;
                delete floats[i];
            }

            for(size_t i = 0; i < strings.size(); i++)
            {
                delete strings[i]->conv_value;
                delete strings[i];
            }
        }

        void CheckInts(int i)
        {
            if(identifiers[i] == "int")
            {
                if(identifiers[i + 2] == ":" && 3 < identifiers.size())
                {
                    ints.push_back(new INT(strc::MakeInt(std::stoi(identifiers[i + 3]), identifiers[i + 1])));
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
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
            bool quote_found = false;
            if(identifiers[i] == "string")
            {
                if(identifiers[i + 2] == ":")
                {
                    int j = 3;
                    std::string output_buffer;
                    if(identifiers[i+3] == "\"")
                    {
                        j++;
                        while(identifiers[i+j] != "\""){
                            output_buffer += identifiers[i+j];
                            j++;

                        }
                    }

                    
                    
                    strings.push_back(new STRING(strc::MakeString(new std::string(output_buffer), identifiers[i + 1])));

                    if(output_buffer == "\\n"){
                        strings.back()->conv_value = new std::string("");
                        strings.back()->sub_instructions.push_back({i, sub_instruction_type::NEWLINE});
                    }
                    else if(output_buffer == "\\t"){
                        strings.back()->conv_value = new std::string("");
                        strings.back()->sub_instructions.push_back({i, sub_instruction_type::TAB});
                    }
                    else if(output_buffer == "\\\\"){
                        strings.back()->conv_value = new std::string("");
                        strings.back()->sub_instructions.push_back({i, sub_instruction_type::BACKSLASH_LIT});
                    }
                    else if(output_buffer == "\\\""){
                        strings.back()->conv_value = new std::string("");
                        strings.back()->sub_instructions.push_back({i, sub_instruction_type::DOUBLE_QUOTE});
                    }
                    else if(output_buffer == "\\\'"){
                        strings.back()->conv_value = new std::string("");
                        strings.back()->sub_instructions.push_back({i, sub_instruction_type::SINGLE_QUOTE});
                    }
                    

                }
                else
                {   
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        std::vector<strc::INT*>& GetInts()
        {
            return ints;
        }

        std::vector<strc::FLOAT*>& GetFloats()
        {
            return floats;
        }

        std::vector<strc::STRING*>& GetStrings()
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
            return m_lexer.GetIdentifiers();
        }

        std::unordered_map<int, std::string>& GetNoFunc(){
            return m_no_func;
        }

    };
}