#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normale;
layout(location = 2) in vec2 coordTex;

uniform mat4 uMVPMatrix = mat4(1.f);

out vec2 vTexCoords;
out vec3 vNormal;


void main() {
	gl_Position = uMVPMatrix * vec4(position, 1.f);
	vNormal = normale;
	vTexCoords = coordTex;
}
