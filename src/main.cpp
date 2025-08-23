#include "../headers/Runtime.hpp"

int main(int argc, char *argv[])
{
    strc::Logger main_logger("StrC");

    if(argc == 1){
        main_logger._log(strc::log_state::ERROR, "Invalid file input");
        main_logger.print_last();
        exit(EXIT_FAILURE);
    }
    else{
        strc::Lexer lexer(argv[1]);

        lexer.lex();

        std::vector<std::string>& id = lexer.GetIdentifiers();

        strc::Parser parser(lexer);
        
        strc::Runtime runtime(parser);

        runtime.run();
        
        parser.ReleaseData();
    }

    

    return 0;
}