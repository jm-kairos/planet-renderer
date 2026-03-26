#version 410 core

in vec3 fragNormal;
in vec3 fragPos;
in float height;

uniform vec3 lightPos;   // Point light position in world space
uniform vec3 camPos;     // Camera position in world space
uniform float u_radius;  // Base planet radius

out vec4 FragColor;

vec3 rockyColor(float heightNorm) {
    vec3 low  = vec3(0.25, 0.22, 0.20);
    vec3 mid  = vec3(0.35, 0.30, 0.25);
    vec3 high = vec3(1.0, 1.0, 1.0);

    float st = smoothstep(0.1, 0.4, heightNorm); 
    float st1 = smoothstep(0.8, 1.0, heightNorm); 

    vec3 p = mid*(1-st) + low*st;
    vec3 p1 = p*(1-st1) + high*st1;

    return p1;
}

void main() {
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);

    float diff = max(dot(N, L), 0.0);
    float ambient = 0.35;

    float lighting = ambient + diff;
    lighting = clamp(lighting, 0.0, 1.0);

    float heightNorm = clamp((length(fragPos) - u_radius) / (u_radius), 0.0, 0.5);
    vec3 baseColor = rockyColor(heightNorm);

    FragColor = vec4(baseColor * lighting, 1.0);
}
