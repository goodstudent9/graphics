#version 330 core
out vec4 FragColor;


struct Material {
    //��������������һ��
    sampler2D diffuse;
    sampler2D specular;    
    sampler2D add_texture;
    float shininess;
}; 

struct Light {
    vec3 position;
    //�����cutoff������ֵ��������ʾ�нǵģ�Ϊ�˼�����ٶȡ�
    vec3 direction;
    float cutoff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float one;
    float two;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    
    
    
    // ������
    vec3 ambient = light.ambient * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
  	
    
   
    //���ﲻ̫��ⷽ��Ϊʲô������
    vec3 lightDir = normalize(light.position - FragPos);
    //�ж��ǲ����ھ۹�Ƶķ�Χ֮�⣺��̫���
    float theta = dot(lightDir,-light.direction);
    
    
    if (theta > light.cutoff)
    {
        //����˥��ϵ��
        float distance = length(light.position - FragPos);
        float attenuation = 1 / (light.constant + light.one * distance + light.two * (distance * distance));
        
        //����������
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * (texture(material.diffuse, TexCoords).rgb + texture(material.add_texture, TexCoords).rgb);
    
        //���㾵�淴��
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
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else//�����û��������;��淴��
    {
       
        FragColor = vec4(ambient, 1.0);

    }
    
   
    
    //����˥��ϵ��
    
} 
