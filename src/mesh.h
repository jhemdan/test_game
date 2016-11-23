#pragma once

#include "types.h"

namespace jaw
{
    class Mesh
    {
    public:
        Mesh();
        
        void create(const float* vertex_data, uint vtx_data_length, const uint* index_data, uint idx_data_length);
        void destroy();
        
        uint get_vbo() const { return vbo; }
        uint get_ibo() const { return ibo; }
        
    private:
        uint vbo;
        uint ibo;
    };
}