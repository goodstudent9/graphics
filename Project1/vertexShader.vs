#version 330 core//定义版本
layout(location = 0) in vec3 apos;//第一个位置的属性
layout(location=1) in vec3 acolor;//第二个位置的属性
out vec3 ourColor;//传给fragment shader的数据
uniform mat4 model;//模型变换矩阵
uniform mat4 view;//观察矩阵
uniform mat4 projection;//投影矩阵

void main() {
	gl_Position = projection * view * model * vec4(apos, 1.0);//对模型的顶点坐标进行三个坐标变换得到最终的三维坐标
	ourColor=acolor;//将颜色值传递给fragment shader
}