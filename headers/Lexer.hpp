#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include "Logger.h"

namespace strc{

    struct Variable{std::string* conv_value;};

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

    INT MakeInt(int value, std::string name)
    {
        INT i = {new std::string(std::to_string(value)), value, name};
        return i;
    }

    struct FLOAT : public Variable
    {
        float value;
        std::string name;
    };

    FLOAT MakeFloat(float value, std::string name)
    {
        FLOAT i = {new std::string(std::to_string(value)), value, name};
        return i;
    }

    struct STRING : public Variable
    {
        std::string name;
        std::vector<SubInstruction> sub_instructions;
    };

    STRING MakeString(std::string* value, std::string name)
    {
        STRING i = {value, name};
        return i;
    }

    struct BOOL : public Variable
    {
        bool value;
        std::string name;
    };

    BOOL MakeBool(bool value, std::string name){
        std::string* s = value ? new std::string("true") : new std::string("false");
        BOOL b = {s, value, name};
        return b;
    }

    static std::string alpha_tokens[] = 
    {
        "int",
        "string",
        "float",
        "print",
        "read",
        "printl",
        "readl"
    };

    static char punct_tokens[] = {
        ':',
        ';',
        '?',
        '!',
        '.',
        '\"'
    };

    class Lexer
    {
    private:
        std::vector<std::string> identifiers;
        std::string m_code;
        int m_position;

        char peek(int ahead = 1) const{
            if(m_position + ahead > m_code.length()){
                return '\0';
            }
            else
            {
                return m_code[m_position];
            }
        }

        char consume()
        {
            return m_code[m_position++];
        }

        template <typename T>
        size_t _Length(T* list){
            return sizeof(list) / sizeof(list[0]);
        }

    public:
        Lexer(std::string file) : m_position(0)
        {
            std::ifstream code;
            
            code.open(file);

            char c;
            while(code.get(c))
            {
                if(c == '\0'){
                    
                }
                else{
                    m_code.push_back(c);
                }
            }

            code.close();

        }
        ~Lexer(){}

        void lex(){
            std::string buffer;
            bool quote_flag = false;
            while(peek() != '\0'){
                if(std::isalpha(peek()))
                {
                    buffer.push_back(consume());
                    while (peek() != '\0' && (std::isalpha(peek()) || peek() == '_'))
                    {
                        buffer.push_back(consume());
                    }

                    //std::cout << buffer << std::endl;

                    identifiers.push_back(buffer);

                    buffer.clear();
                    
                }
                else if(std::isdigit(peek()))
                {
                    buffer.push_back(consume());
                    while (peek() != '\0' && (std::isdigit(peek())  || peek() == '.'))
                    {
                        buffer.push_back(consume());
                    }

                    //std::cout << buffer << std::endl;

                    identifiers.push_back(buffer);

                    buffer.clear();

                }
                else if(std::ispunct(peek()))
                {
                    buffer.push_back(consume());

                    for (int i = 0; i < sizeof(punct_tokens) / sizeof(punct_tokens[0]); i++) {
                        if (buffer[0] == punct_tokens[i]) {
                            identifiers.push_back(buffer);
                            if(identifiers.back() == "\""){
                                quote_flag = !quote_flag;
                            }
                            buffer.clear();
                        }
                    }

                }
                else if (std::isspace(peek()))
                {
                    buffer.push_back(consume());
                    if(quote_flag){
                        identifiers.push_back(buffer);
                    }
                    buffer.clear();
                }
                else if(peek() == '\n'){
                    consume();
                }
            }
        }

        std::vector<std::string>& GetIdentifiers()
        {
            return identifiers;
        }

        std::string GetCode(){
            return m_code;
        }
    };
}