#version 330 core

in vec3 vertexColor;  // Color del v�rtice, pasado desde el vertex shader
out vec4 FragColor;

uniform vec3 uniformColor;  // Color uniforme pasado desde el programa

void main()
{
    if (uniformColor != vec3(0.0, 0.0, 0.0)) {
        FragColor = vec4(uniformColor, 1.0);  // Usar el color uniforme si est� definido
    } else {
        FragColor = vec4(vertexColor, 1.0);  // Usar el color del v�rtice si el color uniforme no est� definido
    }
}

