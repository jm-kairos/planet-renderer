#version 410 core
layout(quads, fractional_even_spacing, ccw) in;

uniform float u_radius;
uniform float u_amplitude;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec2 TextureCoord[];

out vec3 fragNormal;
out vec3 fragPos;

// IQ-style gradient Perlin noise helpers
vec3 randomGradient(vec3 p) {
    float x = fract(sin(dot(p, vec3(127.1, 311.7, 74.7))) * 43758.5453);
    float y = fract(sin(dot(p, vec3(269.5, 183.3, 246.1))) * 43758.5453);
    float z = fract(sin(dot(p, vec3(113.5, 271.9, 124.6))) * 43758.5453);
    return normalize(vec3(x - 0.5, y - 0.5, z - 0.5));
}

//float fade(float t) {
//    return t * t * t * (t * (t * 6 - 15) + 10);
//}
//
//float dfade(float t) {
//    return 30.0 * t * t * (t * (t - 2.0) + 1.0);
//}
//
//// Perlin noise with gradient
//float perlin3D_with_gradient(vec3 p, out vec3 grad) {
//    vec3 i = floor(p);
//    vec3 f = fract(p);
//
//    // Gradient contributions
//    vec3 g000 = randomGradient(i + vec3(0, 0, 0));
//    vec3 g100 = randomGradient(i + vec3(1, 0, 0));
//    vec3 g010 = randomGradient(i + vec3(0, 1, 0));
//    vec3 g110 = randomGradient(i + vec3(1, 1, 0));
//    vec3 g001 = randomGradient(i + vec3(0, 0, 1));
//    vec3 g101 = randomGradient(i + vec3(1, 0, 1));
//    vec3 g011 = randomGradient(i + vec3(0, 1, 1));
//    vec3 g111 = randomGradient(i + vec3(1, 1, 1));
//
//    // Offsets from each corner
//    vec3 pf = f;
//    vec3 pf1 = pf - vec3(1.0, 0.0, 0.0);
//    vec3 pf2 = pf - vec3(0.0, 1.0, 0.0);
//    vec3 pf3 = pf - vec3(1.0, 1.0, 0.0);
//    vec3 pf4 = pf - vec3(0.0, 0.0, 1.0);
//    vec3 pf5 = pf - vec3(1.0, 0.0, 1.0);
//    vec3 pf6 = pf - vec3(0.0, 1.0, 1.0);
//    vec3 pf7 = pf - vec3(1.0, 1.0, 1.0);
//
//    float n000 = dot(g000, pf);
//    float n100 = dot(g100, pf1);
//    float n010 = dot(g010, pf2);
//    float n110 = dot(g110, pf3);
//    float n001 = dot(g001, pf4);
//    float n101 = dot(g101, pf5);
//    float n011 = dot(g011, pf6);
//    float n111 = dot(g111, pf7);
//
//    // Interpolation weights
//    vec3 u = vec3(fade(f.x), fade(f.y), fade(f.z));
//    vec3 du = vec3(dfade(f.x), dfade(f.y), dfade(f.z));
//
//    // Interpolated noise value
//    float nx00 = mix(n000, n100, u.x);
//    float nx10 = mix(n010, n110, u.x);
//    float nx01 = mix(n001, n101, u.x);
//    float nx11 = mix(n011, n111, u.x);
//
//    float nxy0 = mix(nx00, nx10, u.y);
//    float nxy1 = mix(nx01, nx11, u.y);
//
//    float noise = mix(nxy0, nxy1, u.z);
//
//    // Compute gradient analytically
//    vec3 dnx00 = mix(g000, g100, u.x) + du.x * (n100 - n000);
//    vec3 dnx10 = mix(g010, g110, u.x) + du.x * (n110 - n010);
//    vec3 dnx01 = mix(g001, g101, u.x) + du.x * (n101 - n001);
//    vec3 dnx11 = mix(g011, g111, u.x) + du.x * (n111 - n011);
//
//    vec3 dnxy0 = mix(dnx00, dnx10, u.y) + du.y * (nx10 - nx00);
//    vec3 dnxy1 = mix(dnx01, dnx11, u.y) + du.y * (nx11 - nx01);
//
//    grad = mix(dnxy0, dnxy1, u.z) + du.z * (nxy1 - nxy0);
//
//    return noise;
//}
//
//float fbmPerlin(vec3 p, out vec3 totalGrad) {
//    float sum = 0.0;
//    float amp = 1.0;
//    float freq = 4.0;
//    totalGrad = vec3(0.0);
//
//    for (int i = 0; i < 6; ++i) {
//        vec3 grad;
//        float n = perlin3D_with_gradient(p * freq, grad);
//        sum += n * amp;
//        totalGrad += grad * amp * freq;
//        freq *= 2.0;
//        amp *= 0.35;
//    }
//    return sum;
//}
//
//float H(vec3 p, out vec3 grad) {
//    float h = fbmPerlin(p, grad);
//    grad *= u_amplitude;
//    return h * u_amplitude;
//}
//
//// === Ridged FBM ===
//float ridgedNoise(vec3 p, out vec3 grad) {
//    float raw = perlin3D_with_gradient(p, grad);
//    grad *= -sign(raw);  // Flip gradient
//    return 1.0 - abs(raw); // Ridge shape
//}
//
//float fbmRidged(vec3 p, out vec3 totalGrad) {
//    float sum = 0.0;
//    float amp = 1.0;
//    float freq = 2.5;
//    totalGrad = vec3(0.0);
//
//    for (int i = 0; i < 20; ++i) {
//        vec3 grad;
//        float n = ridgedNoise(p * freq, grad);
//        sum += n * amp;
//        totalGrad += grad * amp * freq;
//        freq *= 2.0;
//        amp *= 0.5;
//    }
//    return sum;
//}
//
//// === Final Terrain Height and Gradient ===
//float H_Ridged(vec3 p, out vec3 grad) {
//    float h = fbmRidged(p, grad);
//    h = pow(h, 1.5); // Sharpen peaks
//    grad *= u_amplitude;
//    return h * u_amplitude;
//}
//
//vec3 computeNormal(vec3 sphereDir) {
//    vec3 noiseGrad;
//    H_Ridged(sphereDir, noiseGrad);
//    return normalize(sphereDir - noiseGrad); // sphereDir is radial
//}

float perlin3D_FDM(vec3 p) {

    vec3 i = floor(p);
    vec3 f = fract(p);

    // Fade curve for interpolation
    vec3 u = 6*f*f*f*f*f - 15*f*f*f*f + 10*f*f*f;

    // Compute dot products between gradients and offset vectors
    float n000 = dot(randomGradient(i + vec3(0,0,0)), f - vec3(0,0,0));
    float n100 = dot(randomGradient(i + vec3(1,0,0)), f - vec3(1,0,0));
    float n010 = dot(randomGradient(i + vec3(0,1,0)), f - vec3(0,1,0));
    float n110 = dot(randomGradient(i + vec3(1,1,0)), f - vec3(1,1,0));
    float n001 = dot(randomGradient(i + vec3(0,0,1)), f - vec3(0,0,1));
    float n101 = dot(randomGradient(i + vec3(1,0,1)), f - vec3(1,0,1));
    float n011 = dot(randomGradient(i + vec3(0,1,1)), f - vec3(0,1,1));
    float n111 = dot(randomGradient(i + vec3(1,1,1)), f - vec3(1,1,1));

    // Interpolate all dot products
    float nx00 = mix(n000, n100, u.x);
    float nx10 = mix(n010, n110, u.x);
    float nx01 = mix(n001, n101, u.x);
    float nx11 = mix(n011, n111, u.x);

    float nxy0 = mix(nx00, nx10, u.y);
    float nxy1 = mix(nx01, nx11, u.y);

    return mix(nxy0, nxy1, u.z); // Output in [-1,1]
}

float fbmPerlin_FDM(vec3 p) {
    float e = 0.0; 
    float amp = 1.5;
    float amps = amp;
    float freq = 3.5;
    for (int i = 0; i < 10; ++i) {
        e += perlin3D_FDM(p * freq) * amp;
        freq *= 2.0;
        amp *= 0.35;
        amps += amp;
    }
    e = e/amps;
    return e;
}

float compute_height(vec3 p) {
    float h = fbmPerlin_FDM(p);
    return h * u_amplitude;
}
// Central Finite Difference
vec3 computeNormalsFDM(vec3 sphereDir){

    float dx = 2 * 1/u_radius;
    float dy = 2 * 1/u_radius;
    float dz = 2 * 1/u_radius;

    float sx = 1/dx;
    float sy = 1/dy;
    float sz = 1/dz;
    
    vec3 n = normalize(sphereDir);

    vec3 n_dx = normalize(n + vec3(dx, 0.f, 0.f));
    vec3 n_ddx = normalize(n - vec3(dx, 0.f, 0.f));

    vec3 n_dy = normalize(n + vec3(0.f, dy, 0.f));
    vec3 n_ddy = normalize(n - vec3(0.f, dy, 0.f));

    vec3 n_dz = normalize(n + vec3(0.f, 0.f, dz));
    vec3 n_ddz = normalize(n - vec3(0.f, 0.f, dz));

    float dHdx = sx * (compute_height( n_dx ) - compute_height( n_ddx ) );
    float dHdy = sy * (compute_height( n_dy ) - compute_height( n_ddy ) );
    float dHdz = sz * (compute_height( n_dz ) - compute_height( n_ddz ) );

    return normalize(vec3( -dHdx, -dHdy, -dHdz) + sphereDir);
}

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // Interpolate vertex positions
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = mix(p00, p01, u);
    vec4 p1 = mix(p10, p11, u);

    vec3 sphereDir = normalize(mix(p0, p1, v).xyz);

    // Displace along radial direction

    float height = compute_height(sphereDir);
    vec3 displaced = (u_radius + height) * sphereDir;

    // Final positions and normals
    fragPos = displaced;
    fragNormal = computeNormalsFDM(fragPos); // world-space normal

    gl_Position = projection * view * model * vec4(fragPos, 1.0);

}