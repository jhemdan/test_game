#pragma once

#include "exception.h"

//basic exceptions
namespace jaw
{
    class FileNotFound
        : public Exception
    {
    public:
        explicit FileNotFound(const std::string& file_name)
        {
            this->msg = "File not found: " + file_name;
        }
    };
    
    class CantReadFile
        : public Exception
    {
    public:
        explicit CantReadFile(const std::string& file_name)
        {
            this->msg = "Cannot read file: " + file_name;
        }
    };
    
    class BadFile
        : public Exception
    {
    public:
        explicit BadFile(const std::string& file_name)
        {
            this->msg = "Bad file: " + file_name;
        }
    };
}