#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include "Logger.h"

namespace strc{

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