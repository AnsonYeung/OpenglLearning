#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec4 colorFromVertex;
out vec2 TexCoord;
uniform mat4 transform;

void main() {
    // aPos will actually be a mix of the 3 triangle vertexes coordinates
    gl_Position = transform * vec4(aPos, 1.0);
    colorFromVertex = vec4(aColor, 1.0);
    TexCoord = aTexCoord;
}