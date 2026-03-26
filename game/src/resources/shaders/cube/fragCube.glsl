#version 410 core
out vec4 FragColor;

uniform vec3 ourColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
   //FragColor = texture(texture1, TexCoord);
   FragColor = vec4(ourColor, 1.f);
}

