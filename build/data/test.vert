#version 120

attribute vec2 vertex;
attribute vec2 tex_coords;

uniform mat4 mvp;

varying vec2 frag_tex_coords;

void main()
{
    gl_Position = mvp * vec4(vertex, 0.0, 1.0);
    
    frag_tex_coords = tex_coords;
}