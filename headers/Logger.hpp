#pragma once

#include <iostream>

class Logger
{
private:
    /* data */
public:
    Logger(/* args */){}
    ~Logger(){}

    void Print(){

    }

    void Error(const char* message, const char* error){
        std::cout << "ERROR AT: " << message << ", " << error << std::endl;
    }

    void Warn(){

    }
};
