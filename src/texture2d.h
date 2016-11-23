#pragma once

#include "types.h"
#include "bitmap.h"

namespace jaw
{
    class Texture2d
    {
    public:
        Texture2d();
        ~Texture2d();
        
        void create(const Bitmap& bmp);
        void destroy();
        
        uint get_id() const { return id; }
        int get_w() const { return w; }
        int get_h() const { return h; }
        
    private:
        uint id;
        int w, h;
    };
}