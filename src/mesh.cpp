#include "mesh.h"

#include <GL/glew.h>

namespace jaw
{
    Mesh::Mesh()
    {
        vbo = ibo = 0;
    }
    
    void Mesh::create(const float* vertex_data, uint vtx_data_length, const uint* index_data, uint idx_data_length)
    {
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        
        //todo: static draw, dynamic draw, stream draw
        glBufferData(GL_ARRAY_BUFFER, vtx_data_length * sizeof(float), vertex_data, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_data_length * sizeof(uint), index_data, GL_STATIC_DRAW);
    }
    
    void Mesh::destroy()
    {
        if(vbo)
        {
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ibo);
            vbo = ibo = 0;
        }
    }
}