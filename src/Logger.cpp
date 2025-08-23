#include "../headers/Logger.h"

strc::Logger::Logger(std::string logger_name)
    : m_logger_name(logger_name)
{

}

strc::Logger::~Logger()
{
}

void strc::Logger::_log(strc::log_state state, std::string message)
{
    std::string state_output;
    switch (state)
    {
    case strc::log_state::INFO:
        state_output = "INFO: ";
        break;
    case strc::log_state::WARNING:
        state_output = "WARNING: ";
        break;
    case strc::log_state::ERROR:
        state_output = "ERROR: ";
        break;
    
    default:
        break;
    }
    m_logs.push_back({state, m_logger_name + ": " + state_output + message});
}

void strc::Logger::print_logs()
{
    int errors = 0;
    for (size_t i = 0; i < m_logs.size(); i++)
    {
        std::cout << m_logs[i].message << std::endl;
        m_logs[i].state == strc::log_state::ERROR ? errors++ : errors;
    }
    errors > 0 ? m_errors_found = true : m_errors_found = false;
}

void strc::Logger::print_last()
{
    std::cout << m_logs.back().message << std::endl;
}

inline bool strc::Logger::errors_found()
{
    return m_errors_found;
}
