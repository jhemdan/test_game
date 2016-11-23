#include "exception.h"

namespace jaw
{
    Exception::Exception()
    {
        
    }
    
    Exception::Exception(const std::string& msg)
        : msg(msg)
    {
        
    }
}