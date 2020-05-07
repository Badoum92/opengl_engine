#version 330 core

uniform sampler2D tex_diff0;
uniform sampler2D tex_diff1;
uniform sampler2D tex_diff2;
uniform sampler2D tex_spec0;
uniform sampler2D tex_spec1;
uniform sampler2D tex_spec2;
uniform sampler2D tex_normal0;
uniform sampler2D tex_normal1;
uniform sampler2D tex_normal2;

uniform vec3 u_view_pos;
uniform vec3 u_light_pos;

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_tex_coords;

in vec3 tangent_light_pos;
in vec3 tangent_view_pos;
in vec3 tangent_frag_pos;

out vec4 frag_color;

void main()
{
    // normal
    // vec3 normal = normalize(frag_normal);
    vec3 normal = texture(tex_normal0, frag_tex_coords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    // color
    vec3 color = texture(tex_diff0, frag_tex_coords).rgb;

    // ambient
    vec3 ambient = 0.2 * color;

    // diffuse
    vec3 light_dir = normalize(tangent_light_pos - tangent_frag_pos);
    float diff = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular
    vec3 view_dir = normalize(tangent_view_pos - tangent_frag_pos);
    vec3 reflect_dir = reflect(-light_dir, normal);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    float spec = pow(max(dot(normal, halfway_dir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

    frag_color = vec4(ambient + diffuse + specular, 1.0);
}
