#version 330 core

layout (location = 0) in uint vertex;
layout (location = 1) in vec2 uv;

out vec3 _position;
out vec3 _normal;
out	vec2 _uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

#define POSITION_MASK uint(0x3f)
#define FACE_MASK uint(0x7)

void extractPosition(in uint vertex, out vec3 position)
{
	uint x = vertex >> 26 & POSITION_MASK;
	uint y = vertex >> 20 & POSITION_MASK;
	uint z = vertex >> 14 & POSITION_MASK;
	position = vec3(float(x), float(y), float(z));
}

void faceToNormal(in uint face, out vec3 normal)
{
	switch(face)
	{
		case uint(0):
			normal = vec3(0, 0, 1);
			break;
		case uint(1):
			normal = vec3(0, 0, -1);
			break;
		case uint(2):
			normal = vec3(-1, 0, 0);
			break;
		case uint(3):
			normal = vec3(1, 0, 0);
			break;
		case uint(4):
			normal = vec3(0, 1, 0);
			break;
		case uint(5):
			normal = vec3(0, -1, 0);
			break;
	}
}

void main()
{
	extractPosition(vertex, _position);
	gl_Position = projection * view * model * vec4(_position, 1.0);
	faceToNormal(vertex >> 11 & FACE_MASK, _normal);
	_uv = uv;
}
