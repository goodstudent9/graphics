#version 330 core
out
vec4 FragColor;

//�����Normal��Ҫ��ʼ��
in
vec3 Normal;
in
vec2 TexCoords;
in
vec3 FragPos;

struct Material
{
    float shinness;
    
    sampler2D diffuse;
    sampler2D add_diffuse;
    sampler2D specular;
};

//��main����֮�ⶨ��Ķ����Ͳ���Ҫ�����������롣
//��main����֮�ڶ����������Ҫ�����������롣
//����ƽ�й�Դ
struct DirLight
{
    //ƽ�͹���������,�Ǵӹ�Դ�������ķ���
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight
{
    //�ض�������
    vec3 position;
    
    float constant;
    float one;
    float two;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//����ֱ��Ĺ���
uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirlight;
#define NUM_POINT_LIGHTS 4
uniform PointLight pointLights[NUM_POINT_LIGHTS];
vec3 CalDirLight(DirLight light, vec3 viewDir, vec3 normal, vec3 all_texture, vec3 spec_texture);
vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 all_texture, vec3 spec_texture);
void main()
{
    vec3 material_texture = texture(material.diffuse, TexCoords).rgb + texture(material.add_diffuse, TexCoords).rgb;
    vec3 material_spec = texture(material.specular, TexCoords).rgb;
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    //������գ�
    vec3 out1 = CalDirLight(dirlight, viewDir, normal, material_texture, material_spec);
    //���Դ��
    for (int i = 0; i < 4; i++)
    {
        out1 += CalPointLight(pointLights[i], normal, FragPos, viewDir, material_texture, material_spec);
    }
    FragColor = vec4(out1, 1.0);
        

}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 all_texture, vec3 spec_texture)
{
    //��������˥��ϵ��
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.one * distance + light.two * distance * distance);
    //���㻷������������
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = all_texture * diff * light.diffuse;
    vec3 ambient = all_texture * light.ambient;
    //���㾵�淴���,������reflect������light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shinness);
    vec3 specular = spec_texture * spec * light.specular;
    
    
    vec3 result = ambient + diffuse + specular;
    return (result * attenuation);

}
vec3 CalDirLight(DirLight light, vec3 viewDir, vec3 normal, vec3 all_texture, vec3 spec_texture)
{
    vec3 lightDir = normalize(-light.direction);
    //������Ҫ�۾��ķ���
    float diff = max(dot(normal, lightDir), 0.0);
    
    //mirror light,������˴���Ӧ���Ǹ������ļнǡ�
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shinness);

    vec3 ambient = light.ambient * all_texture;
    vec3 diffuse = light.diffuse * diff * all_texture;
    vec3 specular = light.specular * spec * spec_texture;
    vec3 result = ambient + diffuse + specular;
    return result;
}

//#version 330 core
//out
//vec4 FragColor;

//struct Material
//{
//    sampler2D diffuse;
//    sampler2D add_diffuse;
//    sampler2D specular;
//    float shininess;
//};

//struct DirLight
//{
//    vec3 direction;
	
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};

//struct PointLight
//{
//    vec3 position;
    
//    float constant;
//    float one;
//float two;
	
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
//};

//struct SpotLight
//{
//    vec3 position;
//    vec3 direction;
//    float cutOff;
//    float outerCutOff;
  
//    float constant;
//    float one;
//float two;
  
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
//};

//#define NR_POINT_LIGHTS 4

//in
//vec3 FragPos;
//in
//vec3 Normal;
//in
//vec2 TexCoords;

//uniform vec3 viewPos;
//uniform DirLight dirlight;
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform SpotLight spotLight;
//uniform Material material;

//// function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//void main()
//{
//    // properties
//    vec3 norm = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);
    
//    // == =====================================================
//    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
//    // For each phase, a calculate function is defined that calculates the corresponding color
//    // per lamp. In the main() function we take all the calculated colors and sum them up for
//    // this fragment's final color.
//    // == =====================================================
//    // phase 1: directional lighting
//    vec3 result = CalcDirLight(dirlight, norm, viewDir);
//    // phase 2: point lights
//    for (int i = 0; i < 4; i++)
//        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
//    // phase 3: spot light
//    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
//    FragColor = vec4(result, 1.0);
//}

//// calculates the color when using a directional light.
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(material.add_diffuse,TexCoords) + texture(material.diffuse, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.add_diffuse,TexCoords)+texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    return (ambient + diffuse + specular);
//}

//// calculates the color when using a point light.
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.
//    one * distance
//    +light.two * (distance * distance));
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(material.add_diffuse,TexCoords)+texture(material.diffuse, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.add_diffuse,TexCoords)+texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    //ambient *= attenuation;
//    //diffuse *= attenuation;
//    //specular *= attenuation;
//    return (ambient + diffuse + specular);
//}

//// calculates the color when using a spot light.
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.

//    one * distance

//    +light.two * (distance * distance));
//    // spotlight intensity
//    float theta = dot(lightDir, normalize(-light.direction));
//    float epsilon = light.cutOff - light.outerCutOff;
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(material.add_diffuse,TexCoords)+texture(material.diffuse, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.add_diffuse,TexCoords)+texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    ambient *= attenuation * intensity;
//    diffuse *= attenuation * intensity;
//    specular *= attenuation * intensity;
//    return (ambient + diffuse + specular);
//}