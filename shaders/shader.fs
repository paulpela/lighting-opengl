#version 430 core

in VS_OUT {
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

uniform vec3 diffuseAlbedo = vec3(0.780392, 0.568627, 0.113725);
uniform vec3 specularAlbedo = vec3(0.992157, 0.941176, 0.807843);

uniform float shininess = 128.0;

out vec4 out_color;

const vec4 ambient = vec4(0.329412, 0.223529, 0.027451, 0.8);

void main() {
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.0) * diffuseAlbedo;
    vec3 specular = pow(max(dot(R, V), 0.0), shininess) * specularAlbedo;

    out_color = ambient + vec4(diffuse + specular, 1.0);
}
