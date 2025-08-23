#pragma once

#include <iostream>
#include <vector>

namespace strc
{
    enum class log_state{
        INFO,
        ERROR,
        WARNING
    };

    struct log_message
    {
        log_state state;
        std::string message;
    };

    class Logger
    {
    public:
        Logger(std::string logger_name);
        ~Logger();

        void _log(log_state state, std::string message);
        void print_logs();
        void print_last();
        inline bool errors_found();

    private:
        std::string m_logger_name;
        std::vector<log_message> m_logs;

        bool m_errors_found;
    };

    

}
