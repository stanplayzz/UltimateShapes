#version 150

uniform vec3 color1;
uniform vec3 color2;
uniform int horizontal;

void main() {
	float t;
	if (horizontal == 1) {
		t = gl_TexCoord[0].x;
	} else {
		t = gl_TexCoord[0].y;
	}
	gl_FragColor = vec4(mix(color1, color2, t), 1.0);
}