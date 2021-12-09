#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 3) uniform sampler2D texSampler;

layout(binding = 1) uniform LightUBO {
   vec4 lightPos[5];
   vec4 specColor[5];
   vec4 diffColor[5];
   int lightsInUse;

} lUBO;

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDir[5];
layout(location = 6) in vec3 eyeDir; 
layout(location = 7) in vec2 fragTexCoord;

void main() {
	vec4 ks[5];
	vec4 kd[5];
	for(int i=0; i < lUBO.lightsInUse; i++)	{
		ks[i] = lUBO.specColor[i];
		kd[i] = lUBO.diffColor[i];
	}

	vec4 kt = texture(texSampler, fragTexCoord);
	vec4 ka = 0.1 * kt;

	float diff[5];
	vec3 reflection[5];
	float spec[5];

	for(int i=0; i < lUBO.lightsInUse; i++)	{
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);

		/// Reflection is based incedent which means a vector from the light source, not the direction to the light source
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
		spec[i] = pow(spec[i],14.0);
		
	}
	
	vec4 color = ka;

	for(int i=0; i < lUBO.lightsInUse; i++)	{
		color += (diff[i] * kd[i] * kt) + (spec[i] * ks[i]);
	}

	outColor = color;
}