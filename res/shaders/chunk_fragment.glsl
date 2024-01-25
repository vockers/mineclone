// #version 330 core

// in vec3 _position;
// in vec3 _normal;
// in vec2 _uv;

// uniform sampler2D tex;

// void main()
// {
// 	// ambient
//     float ambientStrength = 0.5;
//     vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
  	
//     // diffuse 
//     vec3 norm = normalize(_normal);
//     // vec3 lightDir = normalize(vec3(0, 50, 0) - _position);
// 	vec3 lightDir = normalize(-vec3(35, -30, 35));
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

// 	vec3 result = ambient + diffuse;
// 	gl_FragColor = vec4(result, 1.0) * texture(tex, _uv);
// }

#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}