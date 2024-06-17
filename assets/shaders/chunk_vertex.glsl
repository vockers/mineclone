#version 330 core

layout (location = 0) in uvec2 vertex;

out float _basicLight;
out	vec2 _uv;
flat out uint _transparent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

#define POSITION_MASK uint(0x3f)
#define POSITION_Y_MASK uint(0xff)
#define FACE_MASK uint(0x7)
#define UV_MASK uint(0x1f)
#define TRANSPARENT_MASK uint(0x1)

void main()
{
	float x = float(vertex.x >> 26 & POSITION_MASK);
	float y = float(vertex.y >> 20 & POSITION_Y_MASK);
	float z = float(vertex.x >> 14 & POSITION_MASK);
	gl_Position = projection * view * model * vec4(x, y, z, 1.0);

	float uv_x = float(vertex.x >> 6 & UV_MASK);
	float uv_y = float(vertex.x >> 1 & UV_MASK);
	_uv = vec2(uv_x / 16, uv_y / 16);

	_basicLight = float((vertex.x >> 11 & FACE_MASK)) / 5.0f;
	_transparent = vertex.x & TRANSPARENT_MASK;
}
