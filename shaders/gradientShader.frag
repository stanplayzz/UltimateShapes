#version 460

uniform sampler2D texture;
uniform vec3 color1;
uniform vec3 color2;
uniform int horizontal;

in vec2 v_texCoord;
out vec4 fragColor;

void main() {
	float t = horizontal == 1 ? v_texCoord.x : v_texCoord.y;
    fragColor = vec4(mix(color1, color2, t), 1.0);
}