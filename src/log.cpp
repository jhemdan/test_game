#include "log.h"

#include <fstream>

namespace jaw
{
    static std::ofstream file;
    
    void init_log()
    {
        file.open("log.txt");
    }
    
    void log_msg(const std::string& msg)
    {
        file << msg;
    }
}