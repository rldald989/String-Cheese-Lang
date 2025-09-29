#include "../headers/Runtime.hpp"

static int position;

char peek(std::string str, int ahead = 1)
{
    if(position + ahead > str.length()){
        return '\0';
    }
    else{
        return str[position];
    }
}

bool contains_file_extension(std::string str, std::string to_find)
{
    std::string buffer;
    bool does_contain = false;
    while (peek(str) != '\0')
    {
        position++;
        if(peek(str) == '.')
        {
            position++;
            while (peek(str) != '\0')
            {
                buffer.push_back(str[position++]);
            }

            if(buffer == to_find){
                does_contain = true;
            }
        
        }
    }
    return does_contain;
}

int main(int argc, char *argv[])
{
    position = 0;
    strc::Logger main_logger("StrC");

    if(argc == 1){
        main_logger._log(strc::log_state::ERROR, "Invalid file input");
        main_logger.print_last();
        exit(EXIT_FAILURE);
    }
    else{

        if(contains_file_extension(argv[1], "strc")){
            strc::Lexer lexer(argv[1]);

            lexer.lex();

            std::vector<std::string>& id = lexer.GetIdentifiers();

            std::string d_input;
            std::cin >> d_input;

            if(d_input == "debug"){
                for(auto& i : id){
                    std::cout << i << std::endl;
                }
            }
            else if(d_input == "testing"){
                
            }
            else{
                main_logger._log(strc::log_state::ERROR, "Invalid command input");
                main_logger.print_last();
                exit(EXIT_FAILURE);
            }

            strc::VariableManager manager;

            strc::Parser parser(lexer, manager);
            
            strc::Runtime runtime(parser, manager);

            runtime.run();
            
            parser.ReleaseData();
        }
        else{
            main_logger._log(strc::log_state::ERROR, "Invalid file input");
            main_logger.print_last();
            exit(EXIT_FAILURE);
        }
        
    }

    return 0;
}