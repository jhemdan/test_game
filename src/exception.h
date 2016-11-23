#pragma once

#include <string>

namespace jaw
{
    class Exception
    {
    public:
        Exception();
        explicit Exception(const std::string& msg);
        
        virtual std::string get_msg() const { return msg; }
        
    protected:
        std::string msg;
    };
}