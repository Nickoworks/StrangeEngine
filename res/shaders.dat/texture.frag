#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform float texture_alpha;
uniform float time;

void main() {
    vec2 uv = TexCoord;
    vec4 color = texture(texture1, uv).rgba;
    color.a *= texture_alpha;
    FragColor = vec4(color);
}
