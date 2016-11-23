#include "log.h"
#include "exception.h"
#include "bitmap.h"
#include "texture2d.h"
#include "shader.h"
#include "mesh.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vecmath/matrix.hpp>

namespace jaw
{
    static SDL_Window* window;
    static SDL_GLContext gl_context;
    static bool should_quit;
    
    static Bitmap test_bmp;
    static Texture2d test_tex;
    static ShaderProg test_prog;
    static Mesh test_mesh;
    
    static vcm::mat4 proj_mat;
    static vcm::mat4 mvp_mat;
    
    void init()
    {
        init_log();
        
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
        
        int x = SDL_WINDOWPOS_UNDEFINED;
        int y = SDL_WINDOWPOS_UNDEFINED;
        int width = 800;
        int height = 600;
        Uint32 flags = SDL_WINDOW_OPENGL;
        
        window = SDL_CreateWindow("Test", x, y, width, height, flags);
        
        if(!window)
        {
            throw Exception(std::string("Could not create window!") + " " + SDL_GetError());
        }
        
        gl_context = SDL_GL_CreateContext(window);
        
        if(!gl_context)
        {
            throw Exception(std::string("Could not create OpenGL context!") + " " + SDL_GetError());
        }
        
        if(glewInit() != GLEW_OK)
        {
            throw Exception("Could not initialize GLEW!");
        }
        
        should_quit = false;
        
        test_bmp.load("data/test.png");
        test_tex.create(test_bmp);
        
        ShaderPart vert, frag;
        vert.load("data/test.vert", SHADER_VERTEX);
        frag.load("data/test.frag", SHADER_FRAGMENT);
        test_prog.create(vert, frag, {{{ "vertex", 0 }, { "tex_coords", 1 }}});
        
        proj_mat = vcm::orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
        
        auto vertex_data =
        {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 100.0f, 0.0f, 1.0f,
            100.0f, 100.0f, 1.0f, 1.0f,
            100.0f, 0.0f, 1.0f, 0.0f
        };
        
        auto index_data =
        {
            0U, 1U, 2U, 2U, 3U, 0U
        };
        
        test_mesh.create(vertex_data.begin(), 16, index_data.begin(), 6);
    }

    void update(float dt)
    {
        
    }

    void render()
    {
        glClearColor(1.0, 0.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, test_tex.get_id());
        
        glUseProgram(test_prog.get_id());
        
        glUniformMatrix4fv(glGetUniformLocation(test_prog.get_id(), "mvp"), 1, 0, &proj_mat[0][0]);
        glUniform1i(glGetUniformLocation(test_prog.get_id(), "tex_map"), 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, test_mesh.get_vbo());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_mesh.get_ibo());
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, false, (4 * sizeof(float)), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, (4 * sizeof(float)), (void*)(2 * sizeof(float)));
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        SDL_GL_SwapWindow(window);
    }

    void run()
    {    
        uint st = 0, et = 0;
        float dt = 1.0f / 60.0f;
        const float ms_to_secs = 1.0f / 1000.0f;
        
        while(!should_quit)
        {        
            st = SDL_GetTicks();
            
            update(dt);
            render();
            
            SDL_Event e;
            while(SDL_PollEvent(&e))
            {
                switch(e.type)
                {
                    case SDL_QUIT:
                        should_quit = true;
                        break;
                    default:
                        break;
                }
            }
            
            et = SDL_GetTicks();
            dt = (et - st) * ms_to_secs;
        }
    }

    void clean()
    {
        test_tex.destroy();
        test_prog.destroy();
        
        if(window)
        {
            SDL_DestroyWindow(window);
        }
        
        IMG_Quit();
        SDL_Quit();
    }
}

int main(int argc, char** argv)
{    
    try
    {
        jaw::init();
        jaw::run();
    }
    catch(const jaw::Exception& e)
    {
        std::cout << e.get_msg() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", e.get_msg().c_str(), nullptr);
    }
    
    jaw::clean();
    
    return 0;
}