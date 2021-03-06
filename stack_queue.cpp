
#include<stdio.h>
#include<string.h>

#include "pch.h"
#include <iostream>
#include <iostream>
#include <stdlib.h> //Needed for "exit" function

  //Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define size 5 //max size of stack
#define MAX 5  //max size of queue

void drawstring(float x, float y, const char *string)
{
	const char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.8f, 0.9f, 0.7f);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

class button
{
	int x1, y1;
	int state;
	char str[10];

public:
	button() {}
	button(int x11, int y11, int x22, int y22, char *str1) {
		x1 = x11;
		y1 = y11;
		x2 = x22;
		y2 = y22;
		state = 1;
		strcpy_s(str, str1);
	}

	void draw() {
		drawstring(x1 + 10, y1 + 10, str);
		glBegin(GL_POINTS);
		for (int i = 0; i < 360; ++i) {
			glVertex2f((cos(3.14159*i / 180.0))*40.0 + x1 + 40, (sin(3.14159*i / 180.0))*40.0 + y1 + 20);
		}
		glEnd();
	}



	void togglestate() {
		state = (state == 1) ? 0 : 1;
	}
	int insidebutton(int x, int y) {
		if (x > x1 && x < x2 && y > y1 && y < y2)
			return 1;
		else return 0;
	}

};
class stack
{
	button s[size];
	int top;

public:
	stack() {
		top = -1;
	}
	int isfull();
	button pop();
	void push(int item);
	int isempty();
	void displaystack();
};
stack st;
///////

int stack::isfull() {
	if (st.top >= size - 1)
		return 1;
	else
		return 0;
}
button stack::pop() {
	button item;
	item = st.s[st.top];
	st.top--;

	return (item);
}
void stack::push(int item) {
	char str[10];
	snprintf(str, sizeof(str), "%d", item);
	button btn(100, 250 + st.top * 50, 150, 300 + st.top * 50, str);
	st.top++;

	st.s[st.top] = btn;

}
int stack::isempty() {
	if (st.top == -1)
		return 1;
	else
		return 0;
}
void stack::displaystack() {
	int i;
	if (st.isempty()) {
		char w[] = " stack is empty!";
		drawstring(10, 10, w);
	}
	else {
		for (i = st.top; i >= 0; i--)
			st.s[i].draw();
	}
}
/////
class queue
{
	button que[MAX];
	int front, rear;
public:
	queue()
	{
		front = -1;
		rear = -1;
	}
	void displayqueue() {
		int i;
		if (front == -1) {
			char w[] = " queue is empty!";
			drawstring(300, 10, w);
		}
		else
		{
			printf(" The queue elements are:\n ");
			for (i = front; i <= rear; i++)
			{
				que[i].draw();
			}
		}
	}
	void insert_element() {
		static int num = 0;
		char str[10];
		snprintf(str, sizeof(str), "%d", num++);
		button btn(300, 250 + rear * 50, 350, 300 + rear * 50, str);
		if (front == 0 && rear == MAX - 1) {
			char w[] = " overflow!";
			drawstring(10, 10, w);
		}
		else if (front == -1 && rear == -1)
		{
			front = rear = 0;
			que[rear] = btn;

		}
		else if (rear == MAX - 1 && front != 0)
		{
			rear = 0;
			que[rear] = btn;
		}
		else
		{
			rear++;
			que[rear] = btn;
		}
	}
	void delete_element() {
		button element;
		if (front == -1)
		{
			char w[] = " Underflow ";
			drawstring(300, 10, w);
		}
		element = que[front];
		if (front == rear)
			front = rear = -1;
		else
		{
			if (front == MAX - 1)
				front = 0;
			else
				front++;
		}
	}
};
queue q;

char push[] = "Push";
char pop[] = "Pop";
char insert[] = "Insert";
char dElete[] = "Delete";

button btn1(100, 100, 175, 150, push);

button btn2(200, 100, 275, 150, pop);
button btn3(300, 100, 375, 150, insert);
button btn4(400, 100, 475, 150, dElete);

void display()
{
	glClearColor(0.5f, 0.2f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	btn1.draw();
	btn2.draw();
	btn3.draw();
	btn4.draw();
	st.displaystack();
	q.displayqueue();
	glFlush();
	glutSwapBuffers();
}
void mouse(int btn, int state, int x, int y)
{
	static int itemno = 0;
	y = 600 - y;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (btn1.insidebutton(x, y))
		{
			btn1.togglestate();
			if (!st.isfull())
				st.push(itemno++);
		}
		if (btn2.insidebutton(x, y))
		{
			btn2.togglestate();
			if (!st.isempty())
				st.pop();

		}
		if (btn3.insidebutton(x, y))
		{
			btn3.togglestate();
			q.insert_element();
		}
		if (btn4.insidebutton(x, y))
		{
			btn4.togglestate();
			q.delete_element();
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (btn1.insidebutton(x, y))
		{
			btn1.togglestate();
		}
		if (btn2.insidebutton(x, y))
		{
			btn2.togglestate();
		}
		if (btn3.insidebutton(x, y))
		{
			btn3.togglestate();
		}
		if (btn4.insidebutton(x, y))
		{
			btn4.togglestate();
		}
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("stack & queue implementation");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutPostRedisplay();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	glutMainLoop();
	return 0;
}
