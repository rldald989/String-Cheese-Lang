#pragma once

#include "Interpreter.hpp"

class StrcMake
{
private:
   std::vector<std::string> identifiers;
   std::vector<std::string> files;
public:
    StrcMake(std::string file)
    {
        std::ifstream code;
        std::string temp;
        
        code.open(file);

        while(code >> temp >> std::ws)
        {
            if(temp == "\0")
            {

            }
            else
            {
                identifiers.push_back(temp);
            }
        }

        code.close();
    }
    ~StrcMake(){

    }

    void Bring()
    {
        for(size_t i = 0; i < identifiers.size(); i++)
        {

        }
    }

    void CheckRun()
    {
        for(size_t i = 0; i < identifiers.size(); i++)
        {
            if(identifiers[i] == "Run")
            {
                
                if(identifiers[i + 1] == "-")
                {
                    std::string atCheck = identifiers[i + 2].substr(0, 1);
                    if(atCheck == "@")
                    {
                        RemoveCharacter(&identifiers[i + 2], '@');
                        files.push_back(identifiers[i + 2]);
                    }
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }
    }

    void CheckP_Run()
    {
        for(size_t i = 0; i < identifiers.size(); i++)
        {
            if(identifiers[i] == "P_Run")
            {
                
                if(identifiers[i + 1] == "-")
                {
                    std::string atCheck = identifiers[i + 2].substr(0, 1);
                    if(atCheck == "@")
                    {
                        RemoveCharacter(&identifiers[i + 2], '@');
                        files.push_back(identifiers[i + 2]);
                    }
                }
                else
                {
                    std::cout << "SYNTAX ERROR AT: " << identifiers[i] << " "  << identifiers[i + 1] << std::endl;
                }
            }
        }
    }

    void Run()
    {
        for(size_t i = 0; i < files.size(); i++){
            strc::Interpreter* tempIntepreter = new strc::Interpreter(files[i]);
            tempIntepreter->Run();
        }
    }

    void Print()
    {
        std::cout << "Files ran: ";
        for(size_t i = 0; i < files.size(); i++)
        {
            std::cout << files[i] << ", " << std::endl;
        }
    }

};