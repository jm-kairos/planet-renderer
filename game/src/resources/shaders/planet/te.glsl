#version 410 core
layout(quads, fractional_even_spacing, ccw) in;

uniform float u_radius;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec2 TextureCoord[];

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec2 t00 = TextureCoord[0];
    vec2 t01 = TextureCoord[1];
    vec2 t10 = TextureCoord[2];
    vec2 t11 = TextureCoord[3];

    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = mix(p00, p01, u);
    vec4 p1 = mix(p10, p11, u);

    vec4 p = mix(p0, p1, v);

    vec3 sphereDir = normalize(p.xyz);
    vec3 displaced = u_radius * sphereDir;

    gl_Position = projection * view * model * vec4(p.xyz, 1.f);

}