#version 330 core//����汾
layout(location = 0) in vec3 apos;//��һ��λ�õ�����
layout(location=1) in vec3 acolor;//�ڶ���λ�õ�����
out vec3 ourColor;//����fragment shader������
uniform mat4 model;//ģ�ͱ任����
uniform mat4 view;//�۲����
uniform mat4 projection;//ͶӰ����

void main() {
	gl_Position = projection * view * model * vec4(apos, 1.0);//��ģ�͵Ķ������������������任�õ����յ���ά����
	ourColor=acolor;//����ɫֵ���ݸ�fragment shader
}