#version 330 core
out
vec4 FragColor;


struct Material
{
    //环境光和漫反射光一样
    sampler2D diffuse;
    sampler2D specular;
    sampler2D add_texture;
    float shininess;
};

struct Light
{
    vec3 position;
    //这里的cutoff是余弦值，用来表示夹角的，为了计算的速度。
    vec3 direction;
    float cutoff;
    float outerCutoff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float one;
    float two;
};

in
vec3 FragPos;
in
vec3 Normal;
in
vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    
    
    
    // 环境光
    vec3 ambient = light.ambient * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
  	
    
   
    //这里不太理解方向为什么是这样
    vec3 lightDir = normalize(light.position - FragPos);
    //判断是不是在聚光灯的范围之外：不太理解
    float theta = dot(lightDir, -light.direction);
    
    
    
        //计算衰减系数
    float distance = length(light.position - FragPos);
    float attenuation = 1 / (light.constant + light.one * distance + light.two * (distance * distance));
        
        //计算漫反射
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
    
        //计算镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 tmpRGB = texture(material.specular, TexCoords).rgb;
        //tmpRGB.x = 1.0 - tmpRGB.x;
        //tmpRGB.y = 1.0 - tmpRGB.y;
        //tmpRGB.z = 1.0 - tmpRGB.z;
    vec3 specular = light.specular * spec * tmpRGB;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    //这里为了模糊边缘，进行了模糊化的操作
    float epsilon = light.cutoff - light.outerCutoff;
    float intense = clamp((theta - light.outerCutoff) / epsilon, 0, 1);
    diffuse *= intense;
    specular *= intense;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
 
    
   
    
    //乘以衰减系数
    
}
