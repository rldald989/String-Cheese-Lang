#include "../headers/Runtime.hpp"



int main(int argc, char *argv[])
{

    strc::Lexer lexer(argv[1]);

    lexer.lex();

    std::vector<std::string>& id = lexer.GetIdentifiers();

    strc::Parser parser(lexer);
    
    strc::Runtime runtime(parser);

    runtime.run();
    
    parser.ReleaseData();

    return 0;
}