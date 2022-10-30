#include<GL/glew.h>
#include<GL/freeglut.h>
GLfloat xRotated, yRotated, zRotated;

void redisplayFunc(void)
{


	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the identity matrix.
	glLoadIdentity();


	glTranslatef(0.0, 0.0, -4.0);
	// Red color used to draw.
	glColor3f(0.8, 0.2, 0.1);
	// changing in transformation matrix.
	// rotation about X axis
	glRotatef(xRotated, 50.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 0.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 0.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a sphere.
	glutSolidSphere(2, 20, 50);
	// Flush buffers to screen

	glFlush();

}

void reshapeFunc(int x, int y)
{
	//if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void idleFunc(void)
{

	yRotated += 0.01;

	redisplayFunc();
}


int main(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	//double buffering used to avoid flickering problem in animation
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// window size
	glutInitWindowSize(400, 350);
	// create the window 
	glutCreateWindow("Sphere Rotating Animation");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Assign  the function used in events
	glutDisplayFunc(redisplayFunc);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);
	//init();

	//Let start glut loop
	glutMainLoop();
	return 0;
}