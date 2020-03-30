#version 400

in vec3 vp;

out vec3 vs_position;

void main () 

{
	vs_position = vp;
	gl_Position = vec4 (vp, 1.0);
}
