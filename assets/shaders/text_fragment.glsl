#version 330 core
in vec2 TexCoords;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, TexCoords).r);
    // vec4 sampled = vec4(0.0, texture(tex, TexCoords).r, 0.0, 1.0);
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * sampled;
    // gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5);
}
