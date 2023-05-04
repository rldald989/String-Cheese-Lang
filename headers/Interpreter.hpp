#pragma once

#include "Parser.hpp"
namespace strc{
    class Interpreter
    {
    private:
        Parser m_parse;
    public:
        Interpreter(std::string file_name) : m_parse(file_name){}
        ~Interpreter(){
        }

        void Print(int i)
        {
            std::vector<std::string>& id = m_parse.GetIdentifiers();
            std::vector<strc::INT*> ints = m_parse.GetInts();
            std::vector<strc::FLOAT*> floats = m_parse.GetFloats();
            std::vector<strc::STRING*> strings = m_parse.GetStrings();
            if(m_parse.GetIdentifiers()[i] == "print")
            {
                if(id[i + 1] == ":")
                {
                    for(int j = 0; j < ints.size(); j++)
                    {
                        if(id[i + 2] == ints[j]->name)
                        {
                            std::cout << ints[j]->value;
                        }
                    }

                    for(int j = 0; j < floats.size(); j++)
                    {
                        if(id[i + 2] == floats[j]->name)
                        {
                            std::cout << floats[j]->value;
                        }
                    }

                    for(int j = 0; j < strings.size(); j++)
                    {
                        if(id[i + 2] == strings[j]->name)
                        {
                            std::cout << strings[j]->value;
                        }
                    }
                }
                else{
                    std::cout << "SYNTAX ERROR AT: " << id[i] << " "  << id[i + 1] << std::endl;
                }
            }
        }

        void PrintLine(int i)
        {
            std::vector<std::string>& id = m_parse.GetIdentifiers();
            std::vector<strc::INT*> ints = m_parse.GetInts();
            std::vector<strc::FLOAT*> floats = m_parse.GetFloats();
            std::vector<strc::STRING*> strings = m_parse.GetStrings();
            if(m_parse.GetIdentifiers()[i] == "printl")
            {
                if(id[i + 1] == ":")
                {
                    for(int j = 0; j < ints.size(); j++)
                    {
                        if(id[i + 2] == ints[j]->name)
                        {
                            std::cout << ints[j]->value << std::endl;
                        }
                    }

                    for(int j = 0; j < floats.size(); j++)
                    {
                        if(id[i + 2] == floats[j]->name)
                        {
                            std::cout << floats[j]->value << std::endl;
                        }
                    }

                    for(int j = 0; j < strings.size(); j++)
                    {
                        if(id[i + 2] == strings[j]->name)
                        {
                            std::cout << strings[j]->value << std::endl;
                        }
                    }
                }
                else{
                    std::cout << "SYNTAX ERROR AT: " << id[i] << " "  << id[i + 1] << std::endl;
                }
            }
        }

        void Read(int i)
        {
            std::vector<std::string>& id = m_parse.GetIdentifiers();
            std::vector<strc::INT*> ints = m_parse.GetInts();
            std::vector<strc::FLOAT*> floats = m_parse.GetFloats();
            std::vector<strc::STRING*> strings = m_parse.GetStrings();
            if(m_parse.GetIdentifiers()[i] == "read")
            {
                if(id[i + 1] == ":")
                {
                    for(int j = 0; j < ints.size(); j++)
                    {
                        if(id[i + 2] == ints[j]->name)
                        {
                            std::cin >> ints[j]->value;
                        }
                    }

                    for(int j = 0; j < floats.size(); j++)
                    {
                        if(id[i + 2] == floats[j]->name)
                        {
                            std::cin >> floats[j]->value;
                        }
                    }

                    for(int j = 0; j < strings.size(); j++)
                    {
                        if(id[i + 2] == strings[j]->name)
                        {
                            std::cin >> strings[j]->value;
                        }
                    }
                }
                else{
                    std::cout << "SYNTAX ERROR AT: " << id[i] << " "  << id[i + 1] << std::endl;
                }
            }
        }

        void ReadLine(int i)
        {
            std::vector<std::string>& id = m_parse.GetIdentifiers();
            std::vector<strc::INT*> ints = m_parse.GetInts();
            std::vector<strc::FLOAT*> floats = m_parse.GetFloats();
            std::vector<strc::STRING*> strings = m_parse.GetStrings();
            if(m_parse.GetIdentifiers()[i] == "readl")
            {
                if(id[i + 1] == ":")
                {
                    for(int j = 0; j < strings.size(); j++)
                    {
                        if(id[i + 2] == strings[j]->name)
                        {
                            std::getline(std::cin, strings[j]->value);
                        }
                    }
                }
                else{
                    std::cout << "SYNTAX ERROR AT: " << id[i] << " "  << id[i + 1] << std::endl;
                }
            }
        }

        bool CheckStandard(int i)
        {
            std::vector<std::string>& id = m_parse.GetIdentifiers();
            if(m_parse.GetIdentifiers()[i] == "-bring")
            {
                if(id[i + 1] == "<standard>")
                {
                    return true;
                }
                else{
                    return false;
                    std::cout << "SYNTAX ERROR AT: " << id[i] << " "  << id[i + 1] << std::endl;
                }
            }
        }

        void Run(){
            for(int i = 0; i < m_parse.GetIdentifiers().size(); i++)
            {
                //std::cout << identifiers[i] << std::endl;
                m_parse.CheckInts(i);
                m_parse.CheckFloats(i);
                m_parse.CheckStrings(i);
                Print(i);
                PrintLine(i);
                Read(i);
                ReadLine(i);
                //PrintIdentifiers();
            }
        }
    };
    
}