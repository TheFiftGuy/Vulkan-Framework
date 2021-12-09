#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform ModelUBO {
    mat4 model;
} mUBO;

layout(binding = 1) uniform LightUBO {
   vec4 lightPos[5];
   vec4 specColor[5];
   vec4 diffColor[5];
   int lightsInUse;

} lUBO;

layout(binding = 2) uniform CameraUBO {
    mat4 view;
    mat4 proj;

} cUBO;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir[5];
layout(location = 6) out vec3 eyeDir; 
layout(location = 7) out vec2 fragTexCoord;

void main() {
    fragTexCoord = inTexCoord;
    mat3 normalMatrix = mat3(transpose(inverse(mUBO.model)));
    vertNormal = normalize(normalMatrix * inNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(cUBO.view * mUBO.model * vec4(inPosition, 1.0)); /// This is the position of the vertex from the origin
    vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;

    for(int i=0; i < lUBO.lightsInUse; i++){     //i < array size of lights
     lightDir[i] = normalize(vec3(lUBO.lightPos[i]) - vertPos); /// Create the light direction.
    }
   
    gl_Position = cUBO.proj * cUBO.view * mUBO.model * vec4(inPosition, 1.0);
}