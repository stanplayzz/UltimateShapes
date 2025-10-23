#version 130

uniform vec3 color1;
uniform vec3 color2;
uniform bool horizontal;

void main()
{
    float t = horizontal ? gl_TexCoord[0].x : gl_TexCoord[0].y;
    gl_FragColor = vec4(mix(color1, color2, t), 1.0);
}