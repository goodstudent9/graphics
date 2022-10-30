#version 330 core
out vec4 FragColor;


struct Material {
    //环境光和漫反射光一样
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    
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

uniform vec3 viewPos;
uniform Material material;
uniform Light lights[3];

void main()
{
    // ambient
    vec3 my_output = vec3(0.0, 0.0, 0.0);
    
    for (int i = 0; i < 3; i++)
    {
        vec3 ambient = lights[i].ambient * material.ambient ;
  	    
    // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lights[i].diffuse * diff * material.diffuse;
    
    // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = lights[i].specular * spec * material.specular;
        
        vec3 result =  ambient+diffuse + specular;
        my_output += result;
        //完成光源的赋值！！
    }
    
    
    FragColor = vec4(my_output, 1.0);
} 
