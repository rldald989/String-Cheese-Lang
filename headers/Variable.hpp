#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Instruction.hpp"

namespace strc
{
    

    enum class sub_instruction_type
    {
        NEWLINE,
        TAB,
        BACKSLASH_LIT,
        DOUBLE_QUOTE,
        SINGLE_QUOTE
    };

    struct SubInstruction{
        int value;
        sub_instruction_type type;
    };

    struct INT : public Variable
    {
        int value;
        std::string name;
    };

    struct FLOAT : public Variable
    {
        float value;
        std::string name;
    };

    struct STRING : public Variable
    {
        std::string name;
    };

    struct BOOL : public Variable
    {
        bool value;
        std::string name;
    };

    enum class operation_type{
        ADD,
        SUB,
        MUL,
        DIV
    };

    class VariableManager
    {
    public:
        VariableManager()
        {

        }
        ~VariableManager()
        {
            
        }

        void ReleaseData()
        {
            for(auto& i : m_ints){
                delete i->conv_value;
                delete i;
            }

            for(auto& f : m_floats){
                delete f->conv_value;
                delete f;
            }

            for(auto& s : m_strings){
                delete s->conv_value;
                delete s;
            }

            for(auto& b : m_bools){
                delete b->conv_value;
                delete b;
            }
        }

        Variable get_value(std::string input_str)
        {
            Variable result;
            bool is_variable = false;
            for(auto& i : m_ints)
            {
                if(i->name == input_str){
                    is_variable = true;
                    result = *i;
                }
                else{
                    continue;
                }
            }
            for(auto& f : m_floats)
            {
                if(f->name == input_str){
                    is_variable = true;
                    result = *f;
                }
                else{
                    continue;
                }
            }
            if(input_str.find('.') != std::string::npos && !is_variable)
            {
                AddFloat(std::stof(input_str), "");
            }
            else if(!is_variable)
            {
                AddInt(std::stoi(input_str), "");
            }
            else{
                std::cout << "SYNTAX ERROR at " << input_str << std::endl;
            }
            return result;
        }

        void PrintValues(){
            for(auto i : m_ints){
                std::cout << i->name << ": " << *i->conv_value << std::endl;
            }

            for(auto f : m_floats){
                std::cout << f->name << ": " << *f->conv_value << std::endl;
            }

            for(auto s : m_strings){
                std::cout << s->name << ": " << *s->conv_value << std::endl;
            }

            for(auto b : m_bools){
                std::cout << b->name << ": " << *b->conv_value << std::endl;
            }
        }

        void AddInt(const int& value, const std::string& name){
            m_ints.push_back(new INT{new std::string(std::to_string(value)), value, name});
        }

        void AddFloat(const float& value, const std::string& name){
            m_floats.push_back(new FLOAT{new std::string(std::to_string(value)), value, name});
        }

        void AddString(std::string* value, const std::string& name){
            m_strings.push_back(new STRING{value, name});
        }

        void AddBool(const bool& value, const std::string& name){
            std::string* s = value ? new std::string("true") : new std::string("false");
            m_bools.push_back(new BOOL{s, value, name});
        }

        void check_variables(const instruction_type& instruction, std::unordered_map<int, Instruction>& instructions, std::string peek, int position)
        {
            for(auto b : m_bools){
                if(peek == b->name){
                    instructions[position] = Instruction({instruction, b->conv_value});
                }
            }
            for(auto i : m_ints){
                if(peek == i->name){
                    instructions[position] = Instruction({instruction, i->conv_value});
                }
            }
            for(auto f : m_floats){
                if(peek == f->name){
                    instructions[position] = Instruction({instruction, f->conv_value});
                }
            }
            for(auto s : m_strings){
                if(peek == s->name){
                    instructions[position] = Instruction({instruction, s->conv_value});
                }
            }
        }

        Variable calculate_operation(std::string a, std::string b, operation_type type)
        {
            Variable _a = get_value(a);
            Variable _b = get_value(b);
            switch (type)
            {
            case operation_type::MUL:
                //return get_value(a) * get_value(b);
                break;
            
            default:
                break;
                
            }
            return {};
        }

    private:
        std::vector<INT*> m_ints;
        std::vector<FLOAT*> m_floats;
        std::vector<STRING*> m_strings;
        std::vector<BOOL*> m_bools;

    };
    
} // namespace strc
