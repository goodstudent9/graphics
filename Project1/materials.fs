#version 330 core
out vec4 FragColor;
struct Material {
    //环境光和漫反射光一样
    sampler2D diffuse;
    sampler2D specular;    
    sampler2D add_texture;
    float shininess;
}; 
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
void main()
{
    // ambient
    vec3 ambient = light.ambient * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 tmpRGB = texture(material.specular, TexCoords).rgb;
    //tmpRGB.x = 1.0 - tmpRGB.x;
    //tmpRGB.y = 1.0 - tmpRGB.y;
    //tmpRGB.z = 1.0 - tmpRGB.z;
    vec3 specular = light.specular * spec * tmpRGB;   
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 
