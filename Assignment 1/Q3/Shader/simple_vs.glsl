#version 440

in vec3 vertex_position;
in vec3 vertex_color;
in vec2 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

void main () 

{
	vs_position = vertex_position;
	vs_color = vertex_color;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);

	gl_Position = vec4(vertex_position, 1.f);
}
