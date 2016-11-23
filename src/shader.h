#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace jaw
{
    enum ShaderType
    {
        SHADER_VERTEX,
        SHADER_FRAGMENT
    };
    
    class ShaderPart
    {
    public:
        ShaderPart();
        ~ShaderPart();
        
        //throws FileNotFound, CantReadFile, BadFile
        void load(const std::string& file_name, ShaderType type);
        void destroy();
        
        uint get_id() const { return id; }
        const std::string& get_file_name() const { return file_name; }
        const std::string& get_src_code() const { return src_code; }
        ShaderType get_type() const { return type; }
        
    private:
        uint id;
        std::string file_name;
        std::string src_code;
        ShaderType type;
    };
    
    struct ShaderAttribMap
    {
        std::vector<std::pair<std::string, int> > locs;
    };
    
    class ShaderProg
    {
    public:
        ShaderProg();
        ~ShaderProg();
        
        //throws Exception
        void create(const ShaderPart& vert, const ShaderPart& frag, const ShaderAttribMap& attribs);
        void destroy();
        
        uint get_id() const { return id; }
        
    private:
        uint id;
    };
}