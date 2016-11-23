#version 120

uniform sampler2D tex_map;

varying vec2 frag_tex_coords;

void main()
{
    gl_FragColor = texture2D(tex_map, frag_tex_coords);
}