#pragma once

#include "Parser.hpp"
#include <map>
#include <string>

namespace strc{

    #define EMPTY "\0"

    static bool safe_range(int min, int max, int index, int variable_size){
        return (min + index >= 0 && max + index < variable_size); 
    }

    class Runtime
    {
    private:
        Parser m_parser;
        VariableManager& m_variable_manager;
        std::vector<std::string>& ids;
        std::unordered_map <int, Variable> m_operations;
        std::unordered_map <int, Instruction> m_instructions;
        int m_position;

        std::string peek(int ahead = 1) const
        {
            if(m_position + ahead > ids.size()){
                return EMPTY;
            }
            else{
                return ids[m_position];
            }
        }

        std::string consume(){
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
            }

            return output_buffer;
        }

    public:
        Runtime(const Parser& parser, VariableManager& manager)
            : m_parser(parser), ids(m_parser.GetIdentifiers()), 
            m_variable_manager(manager),
            m_position(0)
        {
            // Checks for all variable types and adds the variables
            for(int i = 0; i < ids.size(); i++){
                m_parser.CheckBools(i);
                m_parser.CheckFloats(i);
                m_parser.CheckInts(i);
                m_parser.CheckStrings(i);
            }
            
        }
        ~Runtime()
        {
            for(auto & o : m_operations){
                delete o.second.conv_value;
            }
        }

        // Finds an expression within your scope
        std::vector<std::string> find_expr(){
            std::vector<std::string> expression;
            if(peek() == "("){
                m_position++;
                while(peek() != ")"){
                    expression.push_back(consume());
                }
            }
            else{
                expression.push_back(EMPTY);
            }

            return expression;
        }

        void check_operations(std::vector<std::string> buffer){
            for(int b = 0; b < buffer.size(); b++){
                if(safe_range(-1, 1, b, buffer.size())){
                    if(buffer[b] == "*"){
                        m_operations[b] = m_variable_manager.calculate_operation(
                            buffer[b-1], buffer[b+1], 
                            strc::operation_type::MUL);
                    }
                    else if(buffer[b] == "/"){
                        m_operations[b] = m_variable_manager.calculate_operation(
                            buffer[b-1], buffer[b+1], 
                            strc::operation_type::DIV);
                    }
                    else if(buffer[b] == "+"){
                        m_operations[b] = m_variable_manager.calculate_operation(
                            buffer[b-1], buffer[b+1], 
                            strc::operation_type::ADD);
                    }
                    else if(buffer[b] == "-"){
                        m_operations[b] = m_variable_manager.calculate_operation(
                            buffer[b-1], buffer[b+1], 
                            strc::operation_type::SUB);
                    }
                    else{
                        continue;
                    }
                }
                
            }
        }

        // Checks for print statements and adds them to the instructions
        void check_print(instruction_type instruction, std::string instruction_name){
            while(peek() != EMPTY)
            {
                if(peek() == instruction_name)
                {
                    m_position++;
                    if(peek() == ":")
                    {
                        m_position++;
                        if(peek() == "("){
                            std::vector<std::string> buffer;
                            m_position++;
                            while (peek() != ")")
                            {
                                buffer.push_back(consume());
                            }

                            check_operations(buffer);

                            Variable last = m_operations[0];
                            Variable current;
                            for(int i = 0; i < m_operations.size(); i++){
                                current = last + current;
                                last = m_operations[i];
                            }
                            m_instructions[m_position] = Instruction({instruction, current.conv_value});
                        }
                        else if(peek() != "\""){

                            m_variable_manager.check_variables(instruction, m_instructions, peek(), m_position);

                        }
                        else if(peek() != "("){
                            std::string* detected_str = new std::string(detect_string());
                            m_instructions[m_position] = Instruction({instruction, detected_str});
                        }
                        
                    }
                    else if(peek() == " "){
                        continue;
                    }
                    else{
                        std::cout << "SYNTAX ERROR at " << peek() << std::endl;
                    }

                }
                else{
                    m_position++;
                }
            }
            m_position = 0;
        }

        void check_read(instruction_type instruction, std::string instruction_name){
            while(peek() != EMPTY){
                if(peek() == instruction_name){
                    //std::cout << "found print" << std::endl;
                    m_position++;
                    if(peek() == ":"){
                        m_position++;
                        m_variable_manager.check_variables(instruction, m_instructions, peek(), m_position);
                    }
                    else if(peek() == " "){
                        continue;
                    }
                    else{
                        std::cout << "SYNTAX ERROR at " << peek() << std::endl;
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
                Instruction instruction = i.second;
                if(instruction.type == instruction_type::READL){
                    std::getline(std::cin, *instruction.value.conv_value);
                }
                else if(instruction.type == instruction_type::READ){
                    std::cin >> *instruction.value.conv_value;
                }
                else if(instruction.type == instruction_type::PRINT){
                    std::cout << *instruction.value.conv_value;
                }
                else if(instruction.type == instruction_type::PRINTL){
                    std::cout << *instruction.value.conv_value << std::endl;
                }
            }

            for(auto& o : m_operations){
                //std::cout << *o.second.conv_value << std::endl;
            }
        }
    };
    
}