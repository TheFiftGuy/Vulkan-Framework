#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 lightPos;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir;
layout(location = 2) out vec3 eyeDir; 
layout(location = 3) out vec2 fragTexCoord;

void main() {
    fragTexCoord = inTexCoord;
    mat3 normalMatrix = mat3(transpose(inverse(ubo.model)));
    vertNormal = normalize(normalMatrix * inNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(ubo.view * ubo.model * vec4(inPosition, 1.0)); /// This is the position of the vertex from the origin
    vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
    lightDir = normalize(vec3(ubo.lightPos) - vertPos); /// Create the light direction.

    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
  
}