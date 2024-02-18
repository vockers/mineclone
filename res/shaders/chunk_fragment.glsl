#version 330 core

in vec3 _position;
in vec3 _normal;
in vec2 _uv;
flat in uint _transparent;

uniform sampler2D tex;

void main()
{
	// ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
  	
    // diffuse 
    vec3 norm = normalize(_normal);
	vec3 lightDir = normalize(-vec3(35, -30, 35));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

	vec3 result = ambient + diffuse;
    vec4 fragColor = vec4(result, 1.0) * texture(tex, _uv);
    if (_transparent == uint(1))
        fragColor.a = 0.7;
	gl_FragColor = fragColor;
}
