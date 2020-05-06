#version 330 core

uniform sampler2D tex_diff0;
uniform sampler2D tex_diff1;
uniform sampler2D tex_diff2;
uniform sampler2D tex_spec0;
uniform sampler2D tex_spec1;
uniform sampler2D tex_spec2;

uniform vec3 u_view_pos;

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_tex_coords;

out vec4 frag_color;

void main()
{
    vec3 light_pos = vec3(0, 1000, 0);
    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    float intensity = (diff + 0.2);
    frag_color = texture(tex_diff0, frag_tex_coords) * intensity;
}
