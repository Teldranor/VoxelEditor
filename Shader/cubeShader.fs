#version 330

//This shader used Phong model of light (minus specular)
//the ambient light is the light coming a particular light that should affect all other object
//the diffuse light is the light affecting all object turn toward the light
//the specular light is the light is the point of light on shiny object (doesn't work actually)

//A material is a representation of the color of the current object
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
	float alpha;
};

//reprensent a dirLight
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//reprensent a point light
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//represent a spoLight
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//to change is the scene is changed
#define NR_POINT_LIGHTS 1
#define NR_SPOT_LIGHTS 1

//uniform for all lights in the scene
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

//the material used for the current object rendered
uniform Material material;

//the position of the camera (to calculate specular light)
uniform vec3 viewPos;

//position of the point coming from the vertex shader
in vec3 FragPos;
//normal of the point coming from the vertex shader
in vec3 Normal;

//output of the fragment shader (the color of the point)
out vec4 o_color;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

    //calculate directional light
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
    //calculate point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    //calculate spot lights
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
       result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

	o_color = vec4(result, material.alpha);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(-viewDir, -reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    return (ambient + diffuse);
    //vec3 specular = light.specular * spec * material.specular;
    //return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    //vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    //specular *= attenuation;
    return (ambient + diffuse);
    //return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    //vec3 diffuse = light.diffuse * diff * material.diffuse;
    //vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * intensity;
    //diffuse *= attenuation * intensity;
    //specular *= attenuation * intensity;
    return ambient;
    //return (ambient + diffuse + specular);
}
