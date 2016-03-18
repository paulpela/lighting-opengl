#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 v_normal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightDirection;

out VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;

void main() {
    vec4 P = modelViewMatrix * vec4(position, 1.0);
    
    gl_Position = projectionMatrix * P;

    vs_out.N = mat3(modelViewMatrix) * v_normal;
    vs_out.L = lightDirection - P.xyz;
    vs_out.V = -P.xyz;
}
