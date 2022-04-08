#version 330 core
in vec4 colorFromVertex;
in vec2 TexCoord;
out vec4 FragColor;
uniform bool normalizeFlag;
uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

float normalizeColor(float c) {
    return sqrt(255 * 255 * c) / 255;
    // return c * c;
}

void main()
{
    if (normalizeFlag) {
        FragColor = vec4(normalizeColor(colorFromVertex.r), normalizeColor(colorFromVertex.g), normalizeColor(colorFromVertex.b), 1.0f);
    } else {
        FragColor = colorFromVertex;
    }
    FragColor *= mix(texture(ourTexture0, TexCoord), texture(ourTexture1, TexCoord), 0.2);
}
