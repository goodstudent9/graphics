//#include <stdlib.h>
////#include<GL/glew.h>
//#include<GL/freeglut.h>
//
//void init() {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0, 0.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0, 50.0, 0.0, 50.0, -1.0, 1.0);
//}
//
//void display() {
//	GLfloat vertices[3][3] = { {0.0,0.0,0.0}, {25.0, 50.0, 0.0}, {50.0, 0.0, 0.0} };
//	GLfloat p[3] = { 7.5,5.0,0.0 };
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < 5000; ++i) {
//		int x = rand() % 3;
//
//		p[0] = (p[0] + vertices[x][0]) / 2;
//		p[1] = (p[1] + vertices[x][1]) / 2;
//
//		glVertex3fv(p);
//	}
//	glEnd();
//	glFlush();
//}
//
//int main(int argc, char* argv[]) {
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(640, 480);
//	glutInitWindowPosition(200, 200);
//	glutCreateWindow("sierpinski gasket");
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
// 
//
//	return 0;
//}


//#include<gl/glut.h>
//#include<math.h>
//#include<stdlib.h>
//
////a point data type
//typedef GLfloat point3[3];
//
//int n = 20000;//number of recursive steps
//
//// vertices of an arbitrary tetrahedron
//point3 v[] = { {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {0.0, 1.0, -1.0}, {0.0, 0.0, 1.0} };
//
//// arbitrary initial location inside tetrahedron
//point3 p0 = { 0.0, 0.0, 0.0 };
//
//
//void renderScene(void)
//{
//    glClearColor(1.0, 1.0, 1.0, 0.0);//注意事项：要在glClear之前设置color！
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除屏幕及深度缓存
//    glLoadIdentity();// 重置当前的模型观察矩阵
//
//    glBegin(GL_POINTS);//绘制线段
//    glColor3f(0.0f, 0.0f, 1.0f);//设置顶点颜色
//    glVertex2fv(v[0]);
//    glVertex2fv(v[1]);
//    glVertex2fv(v[2]);
//    glVertex2fv(v[3]);
//    glEnd();
//    glBegin(GL_POINTS);
//    for (int i = 0; i < n; i++) {
//        int j = rand() % 4;
//        point3 p1;
//        p1[0] = (p0[0] + v[j][0]) / 2;
//        p1[1] = (p0[1] + v[j][1]) / 2;
//        p1[2] = (p0[2] + v[j][2]) / 2;
//        p0[0] = p1[0];
//        p0[1] = p1[1];
//        p0[2] = p1[2];
//        glVertex2fv(p1);
//        //drawPoint(p1);
//    }
//    glEnd();
//
//    glutSwapBuffers();//当窗口模式为双缓存时，此函数的功能就是把后台缓存的内容交换到前台显示。当然，只有单缓存时，使用它的功能跟用glFlush()一样。而使用双缓存是为了把完整图画一次性显示在窗口上，或者是为了实现动画。
//}
//
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);//初始化GLUT
//    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//设置图形显示模式。GLUT_DEPTH：使用深度缓存；GLUT_DOUBLE：使用双缓存；
//    glutInitWindowPosition(100, 100);//设置窗口显示位置
//    glutInitWindowSize(600, 600);//设置窗口大小
//    glutCreateWindow("Sierpinski");//创建带标题的窗口
//    glutDisplayFunc(renderScene);//为当前窗口设置显示回调函数
//    glutMainLoop();//进入GLUT事件处理循环
//    return 0;
//}


#include<GL/glew.h>
#include <GL/glut.h>

typedef GLfloat point2[2];                                      // define 2d point
typedef GLfloat point3[3];                                      // define 3d point

point2 v2f[] = { {-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15} };    // 2d triagnle end points
point3 v3f[] = { {0.0, 0.0, 1.0},                               // 3d tetrahedron end points
                 {0.0, 0.942809, -0.333333},
                 {-0.816497, -0.471405, -0.333333},
                 {0.816497, -0.471405, -0.333333} };
GLfloat colors3f[4][3] = { {1.0, 0.0, 0.0},                     // color indexes
                           {0.0, 1.0, 0.0},
                           {0.0, 0.0, 1.0},
                           {0.0, 0.0, 0.0} };

int n = 3;                                                      // recursive depth
int h = 600;                                                    // window height
int w = 2 * h;                                                  // window width


void triangle2(point2 a, point2 b, point2 c);                   // draw 2d triangle
void divide_triangle2(point2 a, point2 b, point2 c, int m);     // find 2d middle points recursively
void triangle3(point3 a, point3 b, point3 c);                   // draw 3d triangle
void divide_triangle3(point3 a, point3 b, point3 c, int m);     // find 3d middle points recursively
void Sierpinski2(int m);                                        // draw 2d Sierpinski triangle
void Sierpinski3(int m);                                        // draw 3d Sierpinski triangle
void mydisplay();                                               // display callback funciton
void init();                                                    // initialize window environment


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                                      // initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   // set window configs
    glutInitWindowSize(w, h);                                   // set window size
    glutCreateWindow("Sierpinski");                             // name window
    glutDisplayFunc(mydisplay);                                 // set display callback

    init();                                                     // initialize window
    glutMainLoop();                                             // start main event loop

    return 1;
}

void init()
{
    glEnable(GL_DEPTH_TEST);                                    // enable z-buffer algorithm for hidden-surface removal
    glClearColor(1.0, 1.0, 1.0, 1.0);                           // set background color to white
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // clear color and depth buffer with previously set values

    int w, h;                                                   // get current window width and height
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, w / 2, h);                                 // set view port to left-half window
    glMatrixMode(GL_PROJECTION);                                // set projection range 1
    glLoadIdentity();                                           // set projection range 2
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);                           // set projection range 3
    glMatrixMode(GL_MODELVIEW);                                 // set projection range 4
    glBegin(GL_TRIANGLES);                                      // begin draw triangle
    Sierpinski2(n);                                             // 2d Sierpinski triangle
    glEnd();                                                    // end draw

    glViewport(w / 2, 0, w / 2, h);                             // set view port to right-half window
    glMatrixMode(GL_PROJECTION);                                // set projection range 1, 2, 3, 4
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_TRIANGLES);                                      // begin draw triangle
    Sierpinski3(n);                                             // 3d Sierpinski triangle
    glEnd();                                                    // end draw

    glFlush();                                                  // empty buffer and refresh window
}

void triangle2(point2 a, point2 b, point2 c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void divide_triangle2(point2 a, point2 b, point2 c, int m)
{
    point2 v0, v1, v2;
    if (m > 0) {                                                // expected depth not achieved
        for (int j = 0; j < 2; j++)                             // update three end points of the triangle
        {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        divide_triangle2(a, v0, v1, m - 1);                     // divide three new triangles respectively
        divide_triangle2(b, v0, v2, m - 1);
        divide_triangle2(c, v1, v2, m - 1);
    }
    else {                                                      // expected depth achieved, draw triangle
        triangle2(a, b, c);
    }
}

void triangle3(point3 a, point3 b, point3 c)
{
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
}

void divide_triangle3(point3 a, point3 b, point3 c, int m)
{
    point3 v0, v1, v2;
    if (m > 0) {                                                // expected depth not achieved
        for (int j = 0; j < 3; j++)                             // update three end points of the triangle
        {
            v0[j] = (a[j] + b[j]) / 2;
            v1[j] = (a[j] + c[j]) / 2;
            v2[j] = (b[j] + c[j]) / 2;
        }
        divide_triangle3(a, v0, v1, m - 1);                     // divide three new triangles respectively
        divide_triangle3(b, v0, v2, m - 1);
        divide_triangle3(c, v1, v2, m - 1);
    }
    else {                                                      // expected depth achieved, draw triangle
        triangle3(a, b, c);
    }
}

void Sierpinski2(int m)
{
    glColor3fv(colors3f[3]);                                    // set 2d triangle color
    divide_triangle2(v2f[0], v2f[1], v2f[2], n);                // divide and draw triangles recursively
}

void Sierpinski3(int m)
{
    glColor3fv(colors3f[0]);                                    // set 3d triangle color
    divide_triangle3(v3f[0], v3f[1], v3f[2], m);                // divide and draw triangles recursively
    glColor3fv(colors3f[1]);
    divide_triangle3(v3f[1], v3f[2], v3f[3], m);
    glColor3fv(colors3f[2]);
    divide_triangle3(v3f[0], v3f[2], v3f[3], m);
    glColor3fv(colors3f[3]);
    divide_triangle3(v3f[0], v3f[1], v3f[3], m);
}