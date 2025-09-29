#pragma once

#include <string>

bool is_float(std::string input){
    return input.find('.') != std::string::npos ? true : false;
}

struct Variable
{
    std::string* conv_value;

    Variable operator*(const Variable& other){
        if(is_float(*conv_value))
        {
            return Variable{new std::string(std::to_string(std::stof(*conv_value) * std::stof(*other.conv_value)))};
        }
        else
        {
            return Variable{new std::string(std::to_string(std::stoi(*conv_value) * std::stoi(*other.conv_value)))};
        }
    }

    Variable operator/(const Variable& other){
        if(is_float(*conv_value))
        {
            return Variable{new std::string(std::to_string(std::stof(*conv_value) / std::stof(*other.conv_value)))};
        }
        else
        {
            return Variable{new std::string(std::to_string(std::stoi(*conv_value) / std::stoi(*other.conv_value)))};
        }
    }

    Variable operator+(const Variable& other){
        if(is_float(*conv_value))
        {
            return Variable{new std::string(std::to_string(std::stof(*conv_value) + std::stof(*other.conv_value)))};
        }
        else
        {
            return Variable{new std::string(std::to_string(std::stoi(*conv_value) + std::stoi(*other.conv_value)))};
        }
    }

    Variable operator-(const Variable& other){
        if(is_float(*conv_value))
        {
            return Variable{new std::string(std::to_string(std::stof(*conv_value) - std::stof(*other.conv_value)))};
        }
        else
        {
            return Variable{new std::string(std::to_string(std::stoi(*conv_value) - std::stoi(*other.conv_value)))};
        }
    }
};

enum class instruction_type{
    PRINT,
    PRINTL,
    READ,
    READL
};

// Remember that you don't have to delete any strings from the Instruction's value because it is already deleted by the parser
struct Instruction{
    instruction_type type;
    Variable value;
};