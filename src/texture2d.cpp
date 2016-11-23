#include "texture2d.h"

#include <GL/glew.h>

namespace jaw
{
    Texture2d::Texture2d()
    {
        w = h = 0;
        id = 0;
    }
    
    Texture2d::~Texture2d()
    {
        destroy();
    }
    
    void Texture2d::create(const Bitmap& bmp)
    {
        GLuint tex_id;
        glGenTextures(1, &tex_id);
        
        glBindTexture(GL_TEXTURE_2D, tex_id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        //todo: handle different bpps than 4
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, bmp.get_w(), bmp.get_h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp.get_data());
        
        this->id = tex_id;
        this->w = bmp.get_w();
        this->h = bmp.get_h();
    }
    
    void Texture2d::destroy()
    {
        if(id)
        {
            glDeleteTextures(1, &id);
            id = 0;
            w = h = 0;
        }
    }
}