#version 330 core
layout(location = 0) in vec3 l_position;
layout(location = 1) in vec3 l_normal;
layout(location = 2) in vec2 l_tex_coords;
layout(location = 3) in vec3 l_tangent;
layout(location = 4) in vec3 l_bitangent;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_light_pos;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_tex_coords;
uniform vec3 u_view_pos;

out vec3 tangent_light_pos;
out vec3 tangent_view_pos;
out vec3 tangent_frag_pos;

void main()
{
    frag_normal = l_normal;
    frag_tex_coords = l_tex_coords;
    frag_pos = vec3(u_model * vec4(l_position, 1.0));
    gl_Position = u_projection * u_view * u_model * vec4(frag_pos, 1.0);

    mat3 normal_matrix = transpose(inverse(mat3(u_model)));
    vec3 T = normalize(normal_matrix * l_tangent);
    vec3 N = normalize(normal_matrix * l_normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N));
    tangent_light_pos = TBN * u_light_pos;
    tangent_view_pos = TBN * u_view_pos;
    tangent_frag_pos = TBN * frag_pos;
}
