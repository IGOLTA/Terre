#version 460

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D aTexture;

void main()
{
    fragColor = texture(aTexture, texCoord);
}
