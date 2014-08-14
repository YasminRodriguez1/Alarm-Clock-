#version 130
in vec4 vPosition;
in vec3 vColor;

uniform mat4 model_view;
uniform mat4 projection;

out vec3 outColor;

void
main()
{
    gl_Position = projection * model_view * vPosition;
    gl_Position = gl_Position / gl_Position.w;
    outColor = vColor;
}
