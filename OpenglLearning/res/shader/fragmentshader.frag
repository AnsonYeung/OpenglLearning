#version 330 core
in vec4 colorFromVertex;
out vec4 FragColor;
uniform bool normalizeFlag;

float normalizeColor(float c) {
    return c * c;
}

void main()
{
    if (normalizeFlag) {
        FragColor = vec4(normalizeColor(colorFromVertex.r), normalizeColor(colorFromVertex.g), normalizeColor(colorFromVertex.b), 1.0f);
    } else {
        FragColor = colorFromVertex;
    }
}