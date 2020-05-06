#version 330 core
layout(location = 0) in vec3 l_position;
layout(location = 1) in vec3 l_normal;
layout(location = 2) in vec2 l_tex_coords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_tex_coords;

void main()
{
    frag_pos = vec3(u_model * vec4(l_position, 1.0));
    gl_Position = u_projection * u_view * vec4(frag_pos, 1.0);

    frag_normal = l_normal;
    frag_tex_coords = l_tex_coords;
}
