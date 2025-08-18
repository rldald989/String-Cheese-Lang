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
        Variable* value;
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

        STRING* detect_string(){
            std::string output_buffer;
            STRING* output;
            if(peek() == "\"")
            {
                m_position++;
                while(peek() != "\""){
                    output_buffer += peek();
                    m_position++;
                }
                
                output = new STRING(MakeString(output_buffer, " "));
            }
            else{
                output = {};
            }

            return output;
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
        ~Runtime(){}

        void check_print(){
            while(peek() != "\0"){
                if(peek() == "print"){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        if(peek() != "\""){
                            for(auto& i : m_ints){
                                if(peek() == i->name){
                                    m_instructions[m_position] = Instruction({instruction_type::PRINT, i});
                                }
                            }
                            for(auto& f : m_floats){
                                if(peek() == f->name){
                                    m_instructions[m_position] = Instruction({instruction_type::PRINT, f});
                                }
                            }
                            for(auto& s : m_strings){
                                if(peek() == s->name){
                                    m_instructions[m_position] = Instruction({instruction_type::PRINT, s});
                                }
                            }
                        }
                        else{
                            m_instructions[m_position] = Instruction({instruction_type::PRINT, detect_string()});
                        }
                        
                    }
                    else{
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void check_print_l(){
            while(peek() != "\0"){
                if(peek() == "printl"){
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        if(peek() != "\""){
                            for(auto& i : m_ints){
                            if(peek() == i->name){
                                m_instructions[m_position] = Instruction({instruction_type::PRINTL, i});
                            }
                            }
                            for(auto& f : m_floats ){
                                if(peek() == f->name){
                                    m_instructions[m_position] = Instruction({instruction_type::PRINTL, f});
                                }
                            }
                            for(auto& s : m_strings){
                                if(peek() == s->name){
                                    m_instructions[m_position] = Instruction({instruction_type::PRINTL, s});
                                }
                            }
                        }
                        else{
                            m_instructions[m_position] = Instruction({instruction_type::PRINTL, detect_string()});
                        }
                    }
                    else{
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void check_read(){
            while(peek() != "\0"){
                if(peek() == "read"){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        for(auto& s : m_strings){
                            if(peek() == s->name){
                                m_instructions[m_position] = Instruction({instruction_type::READ, s});
                            }
                        }
                    }
                    else{
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void check_read_l(){
            while(peek() != "\0"){
                if(peek() == "readl"){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        for(auto& s : m_strings){
                            if(peek() == s->name){
                                m_instructions[m_position] = Instruction({instruction_type::READL, s});
                            }
                        }
                    }
                    else{
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void run(){

            check_print();
            check_print_l();
            check_read();
            check_read_l();

            for(auto& i : m_instructions){
                if(i.second.type == instruction_type::READL){
                    std::getline(std::cin, i.second.value->conv_value);
                }
                else if(i.second.type == instruction_type::READ){
                    std::cin >> i.second.value->conv_value;
                }
                else if(i.second.type == instruction_type::PRINT){
                    std::cout << i.second.value->conv_value;
                }
                else if(i.second.type == instruction_type::PRINTL){
                    std::cout << i.second.value->conv_value << std::endl;
                }
                
            }
        }
    };
    
}