#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace jaw
{
    class Bitmap
    {
    public:
        Bitmap();
        
        //throws FileNotFound on failure
        void load(const std::string& file_name);
        
        int get_w() const { return w; }
        int get_h() const { return h; }
        int get_bpp() const { return bpp; }
        int get_pitch() const { return pitch; }
        const ubyte* get_data() const { return data.data(); }
        int get_data_size() const { return (int)data.size(); }
        
    private:
        int w, h;
        int bpp, pitch;
        std::vector<ubyte> data;
    };
}