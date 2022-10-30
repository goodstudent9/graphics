#version 330 core
layout(location=0) in vec3 aPos;

uniform mat4 model2;
uniform mat4 view2;
uniform mat4 projection2;


void main(){
	gl_Position=projection2 * view2 * model2 * vec4(aPos, 1.0);
}