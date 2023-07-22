#include "../headers/StrcMake.hpp"

int main()
{
    std::string StrcMakeFile = "StrcMake.stcm";
    StrcMake strcMake(StrcMakeFile);

    strcMake.CheckRun();
    strcMake.Run();
    strcMake.Print();

    //strc::Interpreter strcInterpreter(fileName);
    //strcInterpreter.Run();
}