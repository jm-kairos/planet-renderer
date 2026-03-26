#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{

	//vec3 sphereCoord = normalize(aPos);
    //gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(mix(aPos, sphereCoord, 1.f), 1.0);

	gl_Position = projection * view * world * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}