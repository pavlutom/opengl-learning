#version 330 core
out vec4 FragColor;
in vec3 vertColor;
in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    FragColor = mix(
        mix(
            texture(tex1, texCoord),
            texture(tex2, texCoord),
            0.4
        ),
        vec4(vertColor, 1.0),
        0.5
    );
}