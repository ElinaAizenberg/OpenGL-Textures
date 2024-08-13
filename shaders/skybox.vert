#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);

    // Use pos.xyww to ensure that the w component is the same for both z and w coordinates.
    // This keeps the depth at the maximum value (far plane) for the entire skybox, making it always appear behind other objects.
    gl_Position = pos.xyww;
}