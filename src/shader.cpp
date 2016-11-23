#include "shader.h"
#include "exceptions.h"
#include "log.h"

#include <fstream>
#include <vector>
#include <GL/glew.h>

namespace jaw
{
    ShaderPart::ShaderPart()
    {
        id = 0;
    }
    
    ShaderPart::~ShaderPart()
    {
        destroy();
    }
    
    void ShaderPart::load(const std::string& file_name, ShaderType type)
    {
        std::ifstream file(file_name, std::ios::in | std::ios::binary | std::ios::ate);
        if(!file)
        {
            throw FileNotFound(file_name);
        }
        
        int file_size = (int)file.tellg();
        file.seekg(0, file.beg);
        
        std::vector<char> buff;
        buff.resize(file_size);
        file.read(buff.data(), file_size);
        
        if(!file)
        {
            throw CantReadFile(file_name);
        }
        
        std::string src = std::string(buff.begin(), buff.end());
        
        GLenum shader_type;
        switch(type)
        {
        default:
        case SHADER_VERTEX:
            shader_type = GL_VERTEX_SHADER;
            break;
        case SHADER_FRAGMENT:
            shader_type = GL_FRAGMENT_SHADER;
            break;
        }
        
        GLuint shader = glCreateShader(shader_type);
        const char* csrc = src.c_str();
        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);
        
        int status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            char buff[512];
            glGetShaderInfoLog(shader, 512, nullptr, buff);
            glDeleteShader(shader);
            
            log_msg(std::string("Shader compile error: ") + buff);
            throw BadFile(file_name);
        }
        
        this->id = shader;
        this->file_name = file_name;
        this->src_code = src;
        this->type = type;
    }
    
    void ShaderPart::destroy()
    {
        if(id)
        {
            glDeleteShader(id);
            this->id = 0;
            this->file_name = "";
            this->src_code = "";
        }
    }
    
    ShaderProg::ShaderProg()
    {
        id = 0;
    }
    
    ShaderProg::~ShaderProg()
    {
        destroy();
    }
    
    void ShaderProg::create(const ShaderPart& vert, const ShaderPart& frag, const ShaderAttribMap& attribs)
    {
        GLuint prog = glCreateProgram();
        
        glAttachShader(prog, vert.get_id());
        glAttachShader(prog, frag.get_id());
        
        for(const auto& p : attribs.locs)
        {
            glBindAttribLocation(prog, p.second, p.first.c_str());
        }
        
        glLinkProgram(prog);
        
        int status;
        glGetProgramiv(prog, GL_LINK_STATUS, &status);
        if(!status)
        {
            char buff[512];
            glGetProgramInfoLog(prog, 512, nullptr, buff);
            glDeleteProgram(prog);
            
            log_msg(std::string("Shader link error: ") + buff);
            
            std::string shader_names = vert.get_file_name() + " and " + frag.get_file_name();
            throw Exception("Could not link shaders " + shader_names);
        }
        
        glDetachShader(prog, vert.get_id());
        glDetachShader(prog, frag.get_id());
        
        this->id = prog;
    }
    
    void ShaderProg::destroy()
    {
        if(id)
        {
            glDeleteProgram(id);
            id = 0;
        }
    }
}