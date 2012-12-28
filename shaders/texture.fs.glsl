#version 330

in vec2 vTexCoords;
in vec3 vNormal;

out vec3 fFragColor;
uniform sampler2D uTexture;

void main() {
    fFragColor = vec3(texture(uTexture, vTexCoords));
}