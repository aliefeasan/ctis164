/*
Ali Efe Asan
22402968
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800
#define D2R 0.01745329252
#define TIMER_ON 1
#define TIMER_PERIOD 16

int  winWidth, winHeight;

int radiusOfFirstCircles = 90, radiusOfFirstCircles2 = 80;
int locX1 = -350, locX2 = 0, locX3 = 350, locY1 = 300;

int onButton1,onButton2,onButton3;

int titleScreen, sceneScreen;

float carX = -450;

float cloudX = -200;
float cloudY = 140;

void circle(int x, int y, int r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 3)
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	glEnd();
}

void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}
void onClick(int button, int state, int x, int y) {
	int oglX = x - winWidth / 2;
	int oglY = -(y - winHeight / 2);

	double distance1 = sqrt(pow(oglX - locX1, 2) + pow(oglY - locY1, 2));
	double distance2 = sqrt(pow(oglX - locX2, 2) + pow(oglY - locY1, 2));
	double distance3 = sqrt(pow(oglX - locX3, 2) + pow(oglY - locY1, 2));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (distance1 <= radiusOfFirstCircles) {
			titleScreen = 1;
			sceneScreen = 0;
		}
		else if (distance2 <= radiusOfFirstCircles) {
			sceneScreen = 1;
			titleScreen = 0;
		}
		else if (distance3 <= radiusOfFirstCircles)
			exit(0);
	}	
}

void drawCar() {
	glColor3ub(255, 255, 255);
	glRectf(carX, -310, carX + 150, -270);

	glColor3ub(220, 220, 220);
	glRectf(carX + 10, -270, carX + 135, -240);

	glColor3ub(173, 216, 230);
	glRectf(carX + 75, -268, carX + 125, -242);

	glColor3ub(173, 216, 230);
	glRectf(carX +15, -268, carX + 65, -242);

	glColor3ub(0, 0, 180);
	glRectf(carX + 10, -295, carX + 140, -285);

	glColor3ub(40, 40, 40);
	glRectf(carX + 40, -240, carX + 110, -232);

	glColor3ub(255, 0, 0);
	glRectf(carX + 75, -232, carX + 105, -225);

	glColor3ub(0, 0, 255);
	glRectf(carX + 45, -232, carX + 75, -225);

	glColor3ub(30, 30, 30);
	circle(carX + 120, -310, 15);

	glColor3ub(180, 180, 180);
	circle(carX + 120, -310, 6);

	glColor3ub(30, 30, 30);
	circle(carX + 30, -310, 15);

	glColor3ub(180, 180, 180);
	circle(carX + 30, -310, 6);

	glColor3ub(255, 255, 150);
	glRectf(carX + 140, -300, carX + 150, -280);

	glColor3ub(0, 0, 0);
	vprint2(carX + 40, -292, 0.15, "POLICE");
}
void drawCloud() {
	glColor3ub(255, 255, 255);
	circle(cloudX, cloudY, 25);
	circle(cloudX - 20, cloudY, 20);
	circle(cloudX + 20, cloudY, 20);
}
void drawMountains() {
	glColor3ub(101, 67, 33);
	glBegin(GL_TRIANGLES);
		glVertex2f(-450, -175);
		glVertex2f(-25, -175);
		glVertex2f(-250, 75);

		glVertex2f(-170, -175);
		glVertex2f(460, -175);
		glVertex2f(150, 150);
	glEnd();
}
void drawHouse() {
	glColor3ub(210, 210, 185);
	glRectf(25, -175, 275, -55);

	glColor3ub(178, 34, 34);
	glBegin(GL_TRIANGLES);
	glVertex2f(-25, -55);
	glVertex2f(325, -55);
	glVertex2f(150, 25);
	glEnd();

	glColor3ub(47, 79, 79);
	glRectf(120, -175, 160, -120);

	glColor3ub(0, 0, 0);
	circle(130, -155, 4);

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex2f(25, -175);
		glVertex2f(275, -175);
		glVertex2f(275, -55);
		glVertex2f(25, -55);
	glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(-25, -55);
		glVertex2f(325, -55);
		glVertex2f(150, 25);
	glEnd();

	glColor3ub(173, 216, 230);
	glRectf(50, -140, 95, -100);
	glRectf(185, -140, 230, -100);

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(50, -140);
		glVertex2f(95, -140);
		glVertex2f(95, -100);
		glVertex2f(50, -100);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(72, -140);
		glVertex2f(72, -100);
		glVertex2f(50, -120);
		glVertex2f(95, -120);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(185, -140);
		glVertex2f(230, -140);
		glVertex2f(230, -100);
		glVertex2f(185, -100);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(207, -140);
		glVertex2f(207, -100);
		glVertex2f(185, -120);
		glVertex2f(230, -120);
	glEnd();
}
void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0, 0, 255);
	circle(locX1, locY1, radiusOfFirstCircles);

	glLineWidth(2.0);
	if (onButton1) {
		glColor3ub(0, 0, 80);
		circle(locX1, locY1, radiusOfFirstCircles2);

		glColor3ub(255, 255, 255);
		vprint2(locX1 - 55, locY1 - 20, 0.35, "TITLE");
	}
	else {
		glColor3ub(0, 0, 150);
		circle(locX1, locY1, radiusOfFirstCircles2);

		glColor3ub(0, 0, 0);
		vprint2(locX1 - 55, locY1 - 20, 0.35, "TITLE");
	}
	
	glColor3ub(255, 0, 0);
	circle(locX2, locY1, radiusOfFirstCircles);
	if (onButton2) {
		glColor3ub(80, 0, 0);
		circle(locX2, locY1, radiusOfFirstCircles2);

		glColor3ub(255, 255, 255);
		vprint2(locX2 - 70, locY1 - 20, 0.35, "SCENE");
	}
	else{
		glColor3ub(150, 0, 0);
		circle(locX2, locY1, radiusOfFirstCircles2);

		glColor3ub(0, 0, 0);
		vprint2(locX2 - 70, locY1 - 20, 0.35, "SCENE");
	}

	glColor3ub(0, 255, 0);
	circle(locX3, locY1, radiusOfFirstCircles);
	if (onButton3) {
		glColor3ub(0, 180, 0);
		circle(locX3, locY1, radiusOfFirstCircles2);

		glColor3ub(255, 255, 255);
		vprint2(locX3 - 50, locY1 - 20, 0.35, "EXIT");
	}
	else{
		glColor3ub(0, 100, 0);
		circle(locX3, locY1, radiusOfFirstCircles2);

		glColor3ub(0, 0, 0);
		vprint2(locX3 - 50, locY1 - 20, 0.35, "EXIT");
	}


	if (titleScreen) {
		glColor3ub(180, 180, 0);
		glRectf(-475, -375, 475, 200);

		glColor3ub(255, 255, 255);
		vprint2(-250, 100, 0.35, "BILKENT UNIVERSITY");
		vprint2(-465, 40, 0.30, "CTIS164-Technical Matematics with Programming");
		vprint2(-200, -20, 0.35, "HOMEWORK #1");
		vprint2(-250, -80, 0.35, "2025-2026 SPRING");

		glColor3ub(255, 0, 0);
		vprint2(-200, -200, 0.30, "ALI EFE ASAN");
		vprint2(-160, -240, 0.30, "22402968");
	}

	if (sceneScreen) {

		glColor3ub(135, 206, 235);
		glRectf(-475, -375, 475, 200);

		glColor3ub(0, 138, 0);
		glRectf(-475, -375, 475, -175);

		drawMountains();

		glColor3ub(80, 80, 80);
		glRectf(-475, -365, 475, -270);

		glBegin(GL_QUADS);
			glVertex2f(0, -270);
			glVertex2f(125, -270); 
			glVertex2f(175, -175); 
			glVertex2f(100, -175);  
		glEnd();
	
		glLineWidth(4);
		glBegin(GL_LINES);
			glColor3ub(180, 180, 0);
			
			glVertex2f(450, -315);
			glVertex2f(400, -315);
			
			glVertex2f(300, -315);
			glVertex2f(200, -315);

			glVertex2f(100, -315);
			glVertex2f(0, -315);

			glVertex2f(-100, -315);
			glVertex2f(-200, -315);

			glVertex2f(-350, -315);
			glVertex2f(-475, -315);
		glEnd();


		//home roof etc
		drawHouse();

		drawCar();
		drawCloud();

		glColor3b(255, 255, 255);
		glRectf(-winWidth / 2, -winHeight / 2, -475, winHeight / 2);
		glRectf(475, -winHeight / 2, winWidth / 2, winHeight / 2);
	}

	glutSwapBuffers();
}

void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	display();
}
void onMove(int x, int y) {
	int oglX = x - winWidth / 2;
	int oglY = -(y - winHeight / 2);
	
	double distance1 = sqrt(pow(oglX - locX1, 2) + pow(oglY - locY1, 2));
	double distance2 = sqrt(pow(oglX - locX2, 2) + pow(oglY - locY1, 2));
	double distance3 = sqrt(pow(oglX - locX3, 2) + pow(oglY - locY1, 2));

	onButton1 = 0;
	onButton2 = 0;
	onButton3 = 0;

	if (distance1<=radiusOfFirstCircles)
		onButton1 = 1;
	if (distance2 <= radiusOfFirstCircles)
		onButton2 = 1;
	if (distance3 <= radiusOfFirstCircles)
		onButton3 = 1;
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	if (sceneScreen) {
		carX += 1.5;
		cloudX -= 1;

		if (carX > 475) {
			carX = -600;
		}

		if (cloudX < -475) {
			cloudX = 600;
		}
	}
	glutPostRedisplay();
}
#endif

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CTIS164 HW1 2025-2026 SPRING - Ali Efe Asan");

	//window
	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	//mouse
	glutPassiveMotionFunc(onMove);
	glutMouseFunc(onClick);
	


#if  TIMER_ON == 1
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif
	glutMainLoop();
	return 0;
}