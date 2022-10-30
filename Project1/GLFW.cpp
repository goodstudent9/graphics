#include<GL/glew.h>
#include<GL/freeglut.h>

#include<iostream>
#include<cstring>
static unsigned int CompilerShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    return id;
}
static unsigned int createShader(std::string& vertexShader, std::string& pixelshader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompilerShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, pixelshader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void helloOpengl(void) {
    //glClearColor(1.0, 1.0, 0.6, 1.0);  //改变默认背景有颜色为浅黄色，要写在glLoadIdentity()前
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glBegin(GL_TRIANGLES);
    {
        //	glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0, 0.3);
        //	glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.3, -0.3);
        //	glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.3, -0.3);
    }
    glEnd();

    //glTranslated(0.3, 0.3, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    /*glBegin(GL_QUADS);
    {
        glVertex3f(-0.2f, 0.2f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.2f, -0.2f, 0.0f);
        glVertex3f(-0.2f, -0.2f, 0.0f);
    }*/
    /*glEnd();*/

    glutSwapBuffers();
}
//void helloOpengl() {
//    float position[6] = {
//        -0.5f, -0.5f,
//        0.5f, 0.5f,
//        0.5f, -0.5f
//    };
//    unsigned int buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
//}




//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(640, 640);
//    glutCreateWindow("GreenTriangle");
//    glutDisplayFunc(helloOpengl);
//    glutMainLoop();
//    return 0;
//}