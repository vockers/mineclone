#version 330 core

in float _basicLight;
in vec2 _uv;
flat in uint _transparent;

uniform sampler2D tex;

void main()
{
    vec4 fragColor = vec4(_basicLight, _basicLight, _basicLight, 1.0) * texture(tex, _uv);
    if (_transparent == uint(1))
        fragColor.a = 0.7;
	gl_FragColor = fragColor;
}
