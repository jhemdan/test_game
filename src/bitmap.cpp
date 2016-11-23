#include "bitmap.h"
#include "exceptions.h"

#include <SDL2/SDL_image.h>
#include <memory.h>

namespace jaw
{    
    Bitmap::Bitmap()
    {
        w = h = 0;
        bpp = pitch = 0;
    }

    void Bitmap::load(const std::string& file_name)
    {
        SDL_Surface* surf = IMG_Load(file_name.c_str());
        if(!surf)
        {
            throw FileNotFound(file_name);
        }
        
        this->w = surf->w;
        this->h = surf->h;
        this->pitch = 4 * this->w;
        this->bpp = surf->format->BytesPerPixel;
        
        this->data.resize(this->pitch * this->h);
        
        int least_pitch = this->pitch < surf->pitch ? this->pitch : surf->pitch;
        ubyte* dest_data = this->data.data();
        ubyte* src_data = (ubyte*)surf->pixels;
        
        for(int i = 0; i < this->h; i++)
        {
            memcpy(dest_data + i * this->pitch, src_data + i * surf->pitch, least_pitch);
        }
        
        SDL_FreeSurface(surf);
    }
}