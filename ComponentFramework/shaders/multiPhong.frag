#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform LightUBO {
   vec4 lightPos[2];
   vec4 specColor[2];
   vec4 diffColor[2];

} lUbo;

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDir[2];
layout(location = 3) in vec3 eyeDir; 
layout(location = 4) in vec2 fragTexCoord;

void main() {
	vec4 ks[2];
	vec4 kd[2];
	for(int i=0; i<2; i++)	{
		ks[i] = lUbo.specColor[i];
		kd[i] = lUbo.diffColor[i];
	}

	vec4 kt = texture(texSampler, fragTexCoord);
	vec4 ka = 0.1 * kt;

	float diff[2];
	vec3 reflection[2];
	float spec[2];

	for(int i=0; i<2; i++)	{
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);

		/// Reflection is based incedent which means a vector from the light source, not the direction to the light source
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
		spec[i] = pow(spec[i],14.0);
		
	}
	
	vec4 color = ka;

	for(int i=0; i<2; i++)	{
		color += (diff[i] * kd[i] * kt) + (spec[i] * ks[i]);
	}

	outColor = color;
}