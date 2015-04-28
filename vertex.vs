#version 330
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
uniform mat4 gWVP;
uniform mat4 gWorld;

out vec3 Normal0;

void main() {
   gl_Position = gWVP * vec4(Position, 1.0);
   Normal0     = vec4(Normal, 0.0).xyz;
}
