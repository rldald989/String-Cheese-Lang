#pragma once

#include "Parser.hpp"
#include <map>
#include <string>

namespace strc{

    enum class instruction_type{
        PRINT,
        PRINTL,
        READ,
        READL
    };

    struct Instruction{
        instruction_type type;
        Variable value;
    };

    class Runtime
    {
    private:
        Parser m_parser;
        std::vector<std::string>& ids;
        std::vector<INT*>& m_ints;
        std::vector<FLOAT*>& m_floats;
        std::vector<STRING*>& m_strings;
        std::unordered_map<int, std::string>& no_func;
        std::map <int, Instruction> m_instructions;
        int m_position;

        std::string peek(int ahead = 1) const
        {
            if(m_position + ahead > ids.size()){
                return "\0";
            }
            else{
                return ids[m_position];
            }
        }

        std::string conusme(){
            return ids[m_position++];
        }

        std::string detect_string(){
            std::string output_buffer;
            if(peek() == "\"")
            {
                m_position++;
                while(peek() != "\""){
                    output_buffer += peek();
                    m_position++;
                }
                if(output_buffer == "\\n"){
                }
            }

            return output_buffer;
        }

    public:
        Runtime(const Parser& parser)
            : m_parser(parser), ids(m_parser.GetIdentifiers()), 
            m_ints(m_parser.GetInts()), m_floats(m_parser.GetFloats()), 
            m_strings(m_parser.GetStrings()), 
            no_func(m_parser.GetNoFunc()),
            m_position(0)
        {
            for(int i = 0; i < ids.size(); i++){
                m_parser.CheckFloats(i);
                m_parser.CheckInts(i);
                m_parser.CheckStrings(i);
                //std::cout << ids[i] << std::endl;
            }
        }
        ~Runtime()
        {
            for(auto& i : m_instructions){
                delete i.second.value.conv_value;
            }
        }

        void check_print(instruction_type instruction, std::string instruction_name){
            while(peek() != "\0"){
                if(peek() == instruction_name){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        if(peek() != "\""){
                            for(auto& i : m_ints){
                                if(peek() == i->name){
                                    m_instructions[m_position] = Instruction({instruction, i->conv_value});
                                }
                            }
                            for(auto& f : m_floats){
                                if(peek() == f->name){
                                    m_instructions[m_position] = Instruction({instruction, f->conv_value});
                                }
                            }
                            for(auto& s : m_strings){
                                if(peek() == s->name){
                                    m_instructions[m_position] = Instruction({instruction, s->conv_value});
                                }
                            }
                        }
                        else{
                            std::string* detected_str = new std::string(detect_string());
                            m_instructions[m_position] = Instruction({instruction, detected_str});
                        }
                        
                    }
                    else{
                        std::cout << "SYNTAX ERROR at " << peek(0) << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void check_read(instruction_type instruction, std::string instruction_name){
            while(peek() != "\0"){
                if(peek() == instruction_name){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        for(auto& s : m_strings){
                            if(peek() == s->name){
                                m_instructions[m_position] = Instruction({instruction, s->conv_value});
                            }
                        }
                    }
                    else{
                        std::cout << "SYNTAX ERROR at " << peek(0) << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void run(){
            check_print(instruction_type::PRINT, "print");
            check_print(instruction_type::PRINTL, "printl");
            check_read(instruction_type::READ, "read");
            check_read(instruction_type::READL, "readl");

            for(auto& i : m_instructions){
                if(i.second.type == instruction_type::READL){
                    std::getline(std::cin, *i.second.value.conv_value);
                }
                else if(i.second.type == instruction_type::READ){
                    std::cin >> *i.second.value.conv_value;
                }
                else if(i.second.type == instruction_type::PRINT){
                    std::cout << *i.second.value.conv_value;
                }
                else if(i.second.type == instruction_type::PRINTL){
                    std::cout << *i.second.value.conv_value << std::endl;
                }
                
            }
        }
    };
    
}