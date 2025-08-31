#pragma once

#include "Lexer.hpp"
#include <string>
#include "Variable.hpp"
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
        VariableManager& m_variable_manager;
        std::vector<std::string>& identifiers;
        Lexer m_lexer;
    public:
        Parser(Lexer& lexer, VariableManager& manager): m_lexer(lexer), identifiers(m_lexer.GetIdentifiers()), m_variable_manager(manager){}
        ~Parser()
        {
            
        }

        void ReleaseData(){
            m_variable_manager.ReleaseData();
        }

        void CheckInts(int i)
        {
            if(identifiers[i] == "int")
            {
                if(identifiers[i + 2] == ":" && i + 3 < identifiers.size())
                {
                    m_variable_manager.AddInt(std::stoi(identifiers[i + 3]), identifiers[i + 1]);
                }
                else if(identifiers[i + 3] == " "){
                        
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }

        void CheckBools(int i)
        {
            if(identifiers[i] == "bool")
            {
                if(identifiers[i + 2] == ":" && i + 3 < identifiers.size())
                {
                    if(identifiers[i + 3] == "true"){
                        m_variable_manager.AddBool(true, identifiers[i + 1]);
                    }
                    else if(identifiers[i + 3] == "false")
                    {
                        m_variable_manager.AddBool(false, identifiers[i + 1]);
                    }
                    else if(identifiers[i + 3] == " "){
                        
                    }
                    else{
                        std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                    }
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
                    m_variable_manager.AddFloat(std::stof(identifiers[i + 3]), identifiers[i + 1]);
                }
                else if(identifiers[i + 3] == " ")
                {
                        
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
                    m_variable_manager.AddString(new std::string(output_buffer), identifiers[i + 1]);

                }
                else
                {   
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
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

    };
}