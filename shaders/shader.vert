#version 330 core
layout(location = 0) in vec3 l_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 frag_pos;

void main()
{
    frag_pos = vec3(u_model * vec4(l_pos, 1.0));
    gl_Position = u_projection * u_view * vec4(frag_pos, 1.0);
}
